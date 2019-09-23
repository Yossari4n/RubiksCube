#ifndef TriggerOut_h
#define TriggerOut_h

#include "MessageManager.h"

class TriggerOut final : public AbstractTriggerOut {
    friend class MessageManager;

public:
    TriggerOut() 
        : m_Owner(nullptr)
        , m_MessageManager(nullptr) { }
    ~TriggerOut() = default;

    Component* Owner() const override { return m_Owner; }

    void Trigger() override { m_MessageManager->ForwardTrigger(this); }

private:
    TriggerOut(Component* owner, MessageManager* message_manager)
        : m_Owner(owner)
        , m_MessageManager(message_manager) { }

    TriggerOut& operator=(const TriggerOut& other) {
        if (this == &other) {
            return *this;
        }

        m_Owner = other.m_Owner;
        m_MessageManager = other.m_MessageManager;

        return *this;
    }

    TriggerOut(const TriggerOut&) = default;
    TriggerOut(TriggerOut&&) = default;
    TriggerOut& operator=(TriggerOut&&) = default;

    Component* m_Owner;
    MessageManager* m_MessageManager;
};

#endif
