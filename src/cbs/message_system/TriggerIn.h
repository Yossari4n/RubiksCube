#ifndef TriggerIn_h
#define TriggerIn_h

#include "MessageManager.h"

template <class O, void(O::* F)()>
class TriggerIn final : public AbstractTriggerIn {
    friend class MessageManager;

public:
    TriggerIn()
        : m_Owner(nullptr) {}
    ~TriggerIn() = default;

    Component* Owner() const { return m_Owner; }

    void Receive() override { (m_Owner->*F)(); }

private:
    TriggerIn(O* owner)
        : m_Owner(owner) {}

    TriggerIn& operator=(const TriggerIn& other) {
        if (this == &other) {
            return *this;
        }

        m_Owner = other.m_Owner;

        return *this;
    }

    TriggerIn(const TriggerIn&) = default;
    TriggerIn(TriggerIn&&) = default;
    TriggerIn& operator=(TriggerIn&&) = default;

    O* m_Owner;
};

#endif
