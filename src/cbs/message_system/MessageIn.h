#ifndef MessageIn_h
#define MessageIn_h

#include "MessageManager.h"
#include "../components/IComponent.h"

class IMessageIn {
    friend class MessageManager;
public:
    IMessageIn(IComponent* owner)
        : m_MessageManager(nullptr)
        , m_Owner(owner) {
    }

    virtual void Receive(void* message) = 0;

protected:
    MessageManager* m_MessageManager;
    IComponent* m_Owner;
};

template <class M, class O, void(O::*F)(M)>
class MessageIn : public IMessageIn {
public:
    MessageIn(O* owner)
        : IMessageIn(owner)
        , m_Component(owner) {
    }

    void Receive(void* message) override;

private:
    O* m_Component;
};

template<class M, class O, void(O::* F)(M)>
inline void MessageIn<M, O, F>::Receive(void* message) {
    (m_Component->*F)(*static_cast<M*>(message));
}

#endif
