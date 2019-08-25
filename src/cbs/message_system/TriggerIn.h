#ifndef TriggerIn_h
#define TriggerIn_h

#include "MessageManager.h"

template <class O, void(O::* F)()>
class TriggerIn : public ITriggerIn {
public:
    MessageIn(O* owner)
        : ITriggerIn(owner)
        , m_Component(owner) {}

    void Receive() override {
        (m_Component->*F)();
    }

private:
    O* m_Component;
};


#endif