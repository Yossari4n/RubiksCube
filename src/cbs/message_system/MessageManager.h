#ifndef MessageManager_h
#define MessageManager_h

#include "../components/IComponent.h"

#include <algorithm>
#include <vector>
#include <unordered_map>

#pragma region InterfacesForwardDeclarations
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
    using PropertyConnection_t = std::pair<IPropertyOut*, IPropertyIn*>;
    using PropertyConnections_t = std::vector<PropertyConnection_t>;
    using MessageConnections_t = std::unordered_map<IMessageOut*, std::vector<IMessageIn*>>;

public:
    /**
     * Type safe managment
     * 
     * TODO docs
     */
    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    template <class T>
    void Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer);

    template <class M, class O, void (O::*F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver);
    
    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M> sender, MessageIn<M, O, F>& receiver);

    void ForwardMessage(IMessageOut* sender, void* message);

    void RemoveConnections(IComponent* component);

private:
    /**
     * Type unsafe managment
     *
     * TODO docs
     */
    void UnsafeConnect(IPropertyOut* subject, IPropertyIn* observer);
    void UnsafeDisconnect(IPropertyOut* subject, IPropertyIn* observer);

    void UnsafeConnect(IMessageOut* sender, IMessageIn* receiver);
    void UnsafeDisconnect(IMessageOut* sender, IMessageIn* receiver);

    PropertyConnections_t m_PropertyConnections;
    MessageConnections_t m_MessageConnections;
};

#pragma region InterfacesImplementations
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

protected:
    virtual void Reset() = 0;

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
#pragma endregion

template <class T>
void MessageManager::Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    if (observer.m_Source == nullptr) {
        observer.m_Source = &subject;

        UnsafeConnect(&subject, &observer);
    } else {
        std::cout << "PropertyIn of type " << typeid(T).name() << " already has connection\n";
    }
}

template <class T>
void MessageManager::Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    UnsafeDisconnect(&subject, &observer);
}

template <class M, class O, void(O::*F)(M)>
void MessageManager::Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
    UnsafeConnect(&sender, &receiver);
}

template <class M, class O, void (O::*F)(M)>
void MessageManager::Disconnect(MessageOut<M> sender, MessageIn<M, O, F>& receiver) {
    UnsafeDisconnect(&sender, &receiver);
}

#endif
