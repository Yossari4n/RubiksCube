#ifndef MessageManager_h
#define MessageManager_h

#include "../components/IComponent.h"

#include <algorithm>
#include <vector>
#include <unordered_map>

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

template <class M, class O, void(O::*F)(M)>
class MessageIn;
#pragma endregion

class MessageManager {
public:
    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    template <class T>
    void Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    void Disconnect(IPropertyOut* subject, IPropertyIn* observer);

    template <class M, class O, void (O::*F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver);
    
    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M> sender, MessageIn<M, O, F>& receiver);

    void Disconnect(IMessageOut* sender, IMessageIn* receiver);

    void ForwardMessage(IMessageOut* sender, void* message);

    void RemoveConnections(IComponent* component);

private:
    std::vector<std::pair<IPropertyOut*, IPropertyIn>> m_PropertyConnections;
    std::unordered_map<IMessageOut*, std::vector<IMessageIn*>> m_MessageConnections;
};


class IPropertyOut {
    friend class MessageManager;

public:
    IPropertyOut(IComponent* owner)
        : m_Owner(owner) {}

private:
    IComponent* m_Owner;
};

class IPropertyIn {
    friend class MessageManager;

public:
    IPropertyIn(IComponent* owner)
        : m_Owner(owner) {}

private:
    IComponent* m_Owner;
};

class IMessageOut {
    friend class MessageManager;

public:
    IMessageOut(IComponent* owner)
        : m_MessageManager(nullptr)
        , m_Owner(owner) {}

protected:
    MessageManager* m_MessageManager;
    IComponent* m_Owner;
};

class IMessageIn {
    friend class MessageManager;

public:
    IMessageIn(IComponent* owner)
        : m_MessageManager(nullptr)
        , m_Owner(owner) {}

    virtual void Receive(void* message) = 0;

protected:
    MessageManager* m_MessageManager;
    IComponent* m_Owner;
};


template <class T>
void MessageManager::Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    if (observer.m_Source != nullptr) {
        observer.m_Source = &subject;
        m_PropertyConnections.emplace(&subject, &observer);
    } else {
        std::cerr << "PropertyIn of type " << typeid(T).name() << " already has connection\n";
    }
}

template <class T>
void MessageManager::Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {

}

template <class M, class O, void(O::*F)(M)>
void MessageManager::Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
    sender.m_MessageManager = this;
    receiver.m_MessageManager = this;
    m_MessageConnections[&sender].push_back(&receiver);
}

template <class M, class O, void (O::*F)(M)>
void MessageManager::Disconnect(MessageOut<M> sender, MessageIn<M, O, F>& receiver) {

}

#endif
