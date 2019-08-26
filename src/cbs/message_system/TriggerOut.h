#ifndef TriggerOut_h
#define TriggerOut_h

#include "MessageManager.h"

class TriggerOut : public ITriggerOut {
public:
    TriggerOut(IComponent* owner)
        : ITriggerOut(owner) {}
    
    void Trigger() {
        if (m_MessageManager != nullptr) {
            m_MessageManager->ForwardTrigger(this);
        }
    }
};

#endif
