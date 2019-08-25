#ifndef TriggerOut_h
#define TriggerOut_h

class MessageManager;

class TriggerOut {
    friend class MessageManager;
public:

private:
    MessageManager* m_MessageManager;
    IComponent* m_Owner;
};

#include "MessageManager.h"

#endif