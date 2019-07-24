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
    template <class M, class T, void (T::* F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, T, F>& receiver);

    void Disconnect(IMessageOut* sender, IMessageIn* receiver);

    void ForwardMessage(IMessageOut* sender, void* message);

    void RemoveConnections(IComponent* component);

private:
    std::unordered_map<IMessageOut*, std::vector<IMessageIn*>> m_MessageConnections;
};


class IPropertyOut {
};

class IPropertyIn {
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


template<class M, class T, void(T::* F)(M)>
void MessageManager::Connect(MessageOut<M>& sender, MessageIn<M, T, F>& receiver) {
    sender.m_MessageManager = this;
    receiver.m_MessageManager = this;
    m_MessageConnections[&sender].push_back(&receiver);
}

#endif
