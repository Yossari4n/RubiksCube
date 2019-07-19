#ifndef MessageOut_h
#define MessageOut_h

#include "MessageManager.h"
#include "../components/IComponent.h"

class IMessageOut {
    friend class MessageManager;
public:
    IMessageOut()
        : m_MessageManager(nullptr) {
    }

protected:
    MessageManager* m_MessageManager;
};

template <class M>
class MessageOut : public IMessageOut {
public:
    MessageOut(IComponent* owner)
        : m_Owner(owner) {
    }

    void Send(M message) {
        if (m_MessageManager != nullptr) {
            m_MessageManager->ForwardMessage(this, &message);
        }
    }

private:
    IComponent* m_Owner;
};

#endif
