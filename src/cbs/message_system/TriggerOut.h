#ifndef TriggerOut_h
#define TriggerOut_h

#include "MessageManager.h"

class TriggerOut : public AbstractTriggerOut {
public:
    TriggerOut(Component* owner)
        : AbstractTriggerOut(owner) {}
    
    void Trigger() {
        if (m_MessageManager != nullptr) {
            m_MessageManager->ForwardTrigger(this);
        }
    }
};

#endif
