#ifndef MessageOut_h
#define MessageOut_h

#include "MessageManager.h"

template <class M>
class MessageOut : public AbstractMessageOut {
public:
    MessageOut(Component* owner)
        : AbstractMessageOut(owner) {}

    void Send(M& message) {
        if (m_MessageManager != nullptr) {
            m_MessageManager->ForwardMessage(this, &message);
        }
    }
};

#endif
