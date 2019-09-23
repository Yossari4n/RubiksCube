#ifndef MessageManager_h
#define MessageManager_h

#include <algorithm>
#include <vector>
#include <unordered_map>

class Component;

#pragma region ForwardDeclarations

class AbstractPropertyOut;
template <class T>
class PropertyOut;

class AbstractPropertyIn;
template <class T>
class PropertyIn;


class AbstractMessageOut;
template <class M>
class MessageOut;

class AbstractMessageIn;
template <class M, class O, void(O::* F)(M)>
class MessageIn;


class AbstractTriggerOut;
class TriggerOut;

class AbstractTriggerIn;
template <class O, void(O::*F)()>
class TriggerIn;

#pragma endregion

class MessageManager {
    using PropertyConnections_t = std::vector<std::pair<AbstractPropertyOut*, AbstractPropertyIn*>>;
    using MessageConnections_t = std::unordered_map<AbstractMessageOut*, std::vector<AbstractMessageIn*>>;
    using TriggerConnections_t = std::unordered_map<AbstractTriggerOut*, std::vector<AbstractTriggerIn*>>;

public:
    template <class T, class ...Args>
    void Make(Component* owner, PropertyOut<T>& to_make, Args&& ...params);

    template <class T>
    void Make(Component* owner, PropertyIn<T>& to_make);

    template <class M>
    void Make(Component* owner, MessageOut<M>& to_make);

    template <class M, class O, void(O::*F)(M)>
    void Make(O* owner, MessageIn<M, O, F>& to_make);

    void Make(Component* owner, TriggerOut& to_make);

    template <class O, void(O::*F)(void)>
    void Make(O* owner, TriggerIn<O, F>& to_make);

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

    void ForwardMessage(AbstractMessageOut* sender, void* message);
    void ForwardTrigger(AbstractTriggerOut* sender);

    void RemoveConnections(Component* component);

private:
    PropertyConnections_t m_PropertyConnections;
    MessageConnections_t m_MessageConnections;
    TriggerConnections_t m_TriggerConnections;
};


#include "ConnectionInterfaces.h"
#include "TriggerOut.h"

template<class T, class ...Args>
void MessageManager::Make(Component* owner, PropertyOut<T>& to_make, Args&& ...params) {
    to_make = PropertyOut<T>(owner, std::forward<Args>(params)...);
}

template<class T>
void MessageManager::Make(Component* owner, PropertyIn<T>& to_make) {
    to_make = PropertyIn<T>(owner);
}

template<class M>
void MessageManager::Make(Component* owner, MessageOut<M>& to_make) {
    to_make = MessageOut<M>(owner, this);
}

template<class M, class O, void(O::*F)(M)>
void MessageManager::Make(O* owner, MessageIn<M, O, F>& to_make) {
    to_make = MessageIn<M, O, F>(owner);
}

template<class O, void(O::* F)(void)>
void MessageManager::Make(O* owner, TriggerIn<O, F>& to_make) {
    to_make = TriggerIn<O, F>(owner);
}

template <class T>
void MessageManager::Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    if (observer.m_Source == nullptr) {
        observer.m_Source = &subject;

        m_PropertyConnections.emplace_back(&subject, &observer);
    } else {
        // TODO DebugLog
    }
}

template <class T>
void MessageManager::Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](std::pair<AbstractPropertyOut*, AbstractPropertyIn*>& pair) { 
                                                   if (pair.first == subject && pair.second == observer) {
                                                       pair.second->RemoveSource();
                                                       return true;
                                                   }
                                                   return false; }));
}

template <class M, class O, void(O::*F)(M)>
void MessageManager::Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
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
    m_TriggerConnections[&sender].push_back(&receiver);
}

template <class O, void(O::* F)()>
void MessageManager::Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
    m_TriggerConnections[&sender].erase(std::remove(m_TriggerConnections[&sender].begin(),
                                                    m_TriggerConnections[&sender].end(),
                                                    receiver));
}

#endif
