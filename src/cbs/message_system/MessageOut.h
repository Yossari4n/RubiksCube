#ifndef MessageOut_h
#define MessageOut_h

#include "MessageManager.h"

template <class M>
class MessageOut final : public AbstractMessageOut {
    friend class MessageManager;

public:
    MessageOut() 
        : m_Owner(nullptr)
        , m_MessageManager(nullptr) { }
    ~MessageOut() = default;

    Component* Owner() const override { return m_Owner; }

    void Send(M& message) {  m_MessageManager->ForwardMessage(this, &message); }

private:
    MessageOut(Component* owner, MessageManager* message_manager)
        : m_Owner(owner)
        , m_MessageManager(message_manager) { }

    MessageOut& operator=(const MessageOut& other) {
        if (this == &other) {
            return *this;
        }

        m_Owner = other.m_Owner;
        m_MessageManager = other.m_MessageManager;

        return *this;
    }

    MessageOut(const MessageOut&) = default;
    MessageOut(MessageOut&&) = default;
    MessageOut& operator=(MessageOut&&) = default;

    Component* m_Owner;
    MessageManager* m_MessageManager;
};

#endif
