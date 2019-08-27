#ifndef MessageOut_h
#define MessageOut_h

#include "MessageManager.h"

template <class M>
class MessageOut : public IMessageOut {
public:
    MessageOut(Component* owner)
        : IMessageOut(owner) {}

    void Send(M message) {
        if (m_MessageManager != nullptr) {
            m_MessageManager->ForwardMessage(this, &message);
        }
    }
};

#endif
