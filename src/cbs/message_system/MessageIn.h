#ifndef MessageIn_h
#define MessageIn_h

#include "MessageManager.h"
#include "../components/IComponent.h"

class IMessageIn {
    friend class MessageManager;
public:
    IMessageIn()
        : m_MessageManager(nullptr) {
    }

    virtual void Receive(void* message) = 0;

protected:
    MessageManager* m_MessageManager;
};

template <class M, class O, void(O::*F)(M)>
class MessageIn : public IMessageIn {
public:
    MessageIn(O* owner)
        : m_Owner(owner) 
        , m_Component(owner) {
    }

    void Receive(void* message) override;

private:
    IComponent* m_Owner;
    O* m_Component;
};

template<class M, class O, void(O::* F)(M)>
inline void MessageIn<M, O, F>::Receive(void* message) {
    (m_Component->*F)(*static_cast<M*>(message));
}

#endif
