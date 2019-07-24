#ifndef MessageIn_h
#define MessageIn_h

#include "MessageManager.h"

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
