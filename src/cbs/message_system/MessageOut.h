#ifndef MessageOut_h
#define MessageOut_h

#include "MessageManager.h"
#include "../components/IComponent.h"

class IMessageOut {
    friend class MessageManager;
public:
    IMessageOut(IComponent* owner)
        : m_MessageManager(nullptr)
        , m_Owner(owner) {
    }

protected:
    MessageManager* m_MessageManager;
    IComponent* m_Owner;
};

template <class M>
class MessageOut : public IMessageOut {
public:
    MessageOut(IComponent* owner)
        : IMessageOut(owner) {
    }

    void Send(M message) {
        if (m_MessageManager != nullptr) {
            m_MessageManager->ForwardMessage(this, &message);
        }
    }
};

#endif
