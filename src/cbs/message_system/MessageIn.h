#ifndef MessageIn_h
#define MessageIn_h

#include "MessageManager.h"

template <class M, class O, void(O::* F)(M)>
class MessageIn : public AbstractMessageIn {
public:
    MessageIn(O* owner)
        : AbstractMessageIn(owner)
        , m_Component(owner) {}

    void Receive(void* message) override {
        (m_Component->*F)(*static_cast<M*>(message));
    }

private:
    O* m_Component;
};

#endif
