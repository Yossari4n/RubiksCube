#ifndef MessageManager_h
#define MessageManager_h

#include <algorithm>
#include <vector>
#include <unordered_map>

class Component;

#pragma region ForwardDeclarations
class IPropertyOut;

template <class T>
class PropertyOut;

class IPropertyIn;

template <class T>
class PropertyIn;


class IMessageOut;

template <class M>
class MessageOut;

class IMessageIn;

template <class M, class O, void(O::* F)(M)>
class MessageIn;


class ITriggerOut;

class TriggerOut;

class ITriggerIn;

template <class O, void(O::*F)()>
class TriggerIn;
#pragma endregion

class MessageManager {
    using PropertyConnections_t = std::vector<std::pair<IPropertyOut*, IPropertyIn*>>;
    using MessageConnections_t = std::unordered_map<IMessageOut*, std::vector<IMessageIn*>>;
    using TriggerConnections_t = std::unordered_map<ITriggerOut*, std::vector<ITriggerIn*>>;

public:
    /**
     * Type safe managment
     * 
     * Connects and disconnects pipe-out and pipe-in with additional compile-time type check.
     */
    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    template <class T>
    void Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    template <class M, class O, void (O::*F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver);

    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver);

    template <class O, void (O::* F)(void)>
    void Connect(TriggerOut& sender, TriggerIn<O, F>& receiver);

    template <class O, void (O::* F)(void)>
    void Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver);

    void ForwardMessage(IMessageOut* sender, void* message);
    void ForwardTrigger(ITriggerOut* sender);

    void RemoveConnections(Component* component);

private:
    PropertyConnections_t m_PropertyConnections;
    MessageConnections_t m_MessageConnections;
    TriggerConnections_t m_TriggerConnections;
};

#pragma region InterfacesImplementations
/**************
 *  Property  *
 **************/

class IPropertyOut {
    friend class MessageManager;

public:
    IPropertyOut(Component* owner)
        : m_Owner(owner) {}

    IPropertyOut() = delete;
    IPropertyOut(const IPropertyOut&) = delete;
    IPropertyOut& operator=(const IPropertyOut&) = delete;
    IPropertyOut(IPropertyOut&&) = delete;
    IPropertyOut operator=(IPropertyOut&&) = delete;
    virtual ~IPropertyOut() = default;

    Component* Owner() const { return m_Owner; }

private:
    Component* m_Owner;
};

class IPropertyIn {
    friend class MessageManager;

public:
    IPropertyIn(Component* owner)
        : m_Owner(owner) {}

    IPropertyIn() = delete;
    IPropertyIn(const IPropertyIn&) = delete;
    IPropertyIn& operator=(const IPropertyIn&) = delete;
    IPropertyIn(IPropertyIn&&) = delete;
    IPropertyIn operator=(IPropertyIn&&) = delete;
    virtual ~IPropertyIn() = default;

    Component* Owner() const { return m_Owner; }

protected:
    virtual void Reset() = 0;

private:
    Component* m_Owner;
};


/***************
 *   Message   *
 ***************/

class IMessageOut {
    friend class MessageManager;

public:
    IMessageOut(Component* owner)
        : m_MessageManager(nullptr)
        , m_Owner(owner) {}

    IMessageOut() = delete;
    IMessageOut(const IMessageOut&) = delete;
    IMessageOut& operator=(const IMessageOut&) = delete;
    IMessageOut(IMessageOut&&) = delete;
    IMessageOut operator=(IMessageOut&&) = delete;
    virtual ~IMessageOut() = default;

    Component* Owner() const { return m_Owner; }

protected:
    MessageManager* m_MessageManager;

private:
    Component* m_Owner;
};

class IMessageIn {
    friend class MessageManager;

public:
    IMessageIn(Component* owner)
        :  m_Owner(owner) {}

    IMessageIn() = delete;
    IMessageIn(const IMessageIn&) = delete;
    IMessageIn& operator=(const IMessageIn&) = delete;
    IMessageIn(IMessageIn&&) = delete;
    IMessageIn operator=(IMessageIn&&) = delete;
    virtual ~IMessageIn() = default;

    virtual void Receive(void* message) = 0;

    Component* Owner() const { return m_Owner; }

private:
    Component* m_Owner;
};


/*************
 *  Trigger  *
 *************/

class ITriggerOut {
    friend class MessageManager;

public:
    ITriggerOut(Component* owner)
        : m_MessageManager(nullptr)
        , m_Owner(owner) {}

    ITriggerOut() = delete;
    ITriggerOut(const ITriggerOut&) = delete;
    ITriggerOut& operator=(const ITriggerOut&) = delete;
    ITriggerOut(ITriggerOut&&) = delete;
    ITriggerOut operator=(ITriggerOut&&) = delete;
    virtual ~ITriggerOut() = default;

    Component* Owner() const { return m_Owner; }

protected:
    MessageManager* m_MessageManager;

private:
    Component* m_Owner;
};

class ITriggerIn {
    friend class MessageManager;

public:
    ITriggerIn(Component* owner)
        : m_Owner(owner) {}

    ITriggerIn() = delete;
    ITriggerIn(const ITriggerIn&) = delete;
    ITriggerIn& operator=(const ITriggerIn&) = delete;
    ITriggerIn(ITriggerIn&&) = delete;
    ITriggerIn operator=(ITriggerIn&&) = delete;
    virtual ~ITriggerIn() = default;

    virtual void Receive() = 0;

    Component* Owner() const { return m_Owner; }

private:
    Component* m_Owner;
};
#pragma endregion
#include "TriggerOut.h"

template <class T>
void MessageManager::Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    if (observer.m_Source == nullptr) {
        observer.m_Source = &subject;

        m_PropertyConnections.emplace_back(&subject, &observer);
    } else {
        // TODO DebugLog
        std::cout << "PropertyIn of type " << typeid(T).name() << " already has connection\n";
    }
}

template <class T>
void MessageManager::Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](std::pair<IPropertyOut*, IPropertyIn*>& pair) { 
                                                   if (pair.first == subject && pair.second == observer) {
                                                       pair.second->Reset();
                                                       return true;
                                                   }
                                                   return false; }));
}

template <class M, class O, void(O::*F)(M)>
void MessageManager::Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
    sender.m_MessageManager = this;
    m_MessageConnections[&sender].push_back(&receiver);
}

template <class M, class O, void (O::*F)(M)>
void MessageManager::Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
    m_MessageConnections[&sender].erase(std::remove(m_MessageConnections[&sender].begin(), 
                                                    m_MessageConnections[&sender].end(), 
                                                    receiver));
}

template <class O, void(O::* F)()>
void MessageManager::Connect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
    sender.m_MessageManager = this;
    m_TriggerConnections[&sender].push_back(&receiver);
}

template <class O, void(O::* F)()>
void MessageManager::Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
    m_TriggerConnections[&sender].erase(std::remove(m_TriggerConnections[&sender].begin(),
                                                    m_TriggerConnections[&sender].end(),
                                                    receiver));
}

#endif
