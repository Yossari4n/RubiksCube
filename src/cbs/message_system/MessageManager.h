#ifndef MessageManager_h
#define MessageManager_h

#include <vector>
#include <unordered_map>

class IMessageOut;

template <class M>
class MessageOut;

class IMessageIn;

template <class M, class O, void(O::*F)(M)>
class MessageIn;

class MessageManager {
public:
    MessageManager(int id)
        : id_test(id) {

    }

    template <class M, class T, void (T::* F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, T, F>& receiver);

    void ForwardMessage(IMessageOut* sender, void* message);

private:
    int id_test;
    std::unordered_map<IMessageOut*, std::vector<IMessageIn*>> m_MessageConnections;
};

#include "MessageOut.h"
#include "MessageIn.h"

template<class M, class T, void(T::* F)(M)>
inline void MessageManager::Connect(MessageOut<M>& sender, MessageIn<M, T, F>& receiver){
    sender.m_MessageManager = this;
    receiver.m_MessageManager = this;
    m_MessageConnections[&sender].push_back(&receiver);
}

#endif
