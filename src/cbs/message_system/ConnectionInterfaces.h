#ifndef ConnectionInterfaces_h
#define ConnectionInterfaces_h

#include "MessageManager.h"

class ConnectionPipe {
    friend class MessageManager;

public:
    ConnectionPipe(Component* owner)
        : m_Owner(owner)
        , m_MessageManager(nullptr) {}

    ConnectionPipe() = delete;
    ConnectionPipe(const ConnectionPipe&) = delete;
    ConnectionPipe& operator=(const ConnectionPipe&) = delete;
    ConnectionPipe(ConnectionPipe&&) = delete;
    ConnectionPipe& operator=(ConnectionPipe&&) = delete;
    virtual ~ConnectionPipe() = default;

    Component* Owner() { return m_Owner; }

protected:
    Component* m_Owner;
    MessageManager* m_MessageManager;
};

/**************
 *  Property  *
 **************/

class AbstractPropertyOut : public ConnectionPipe {
    friend class MessageManager;

public:
    AbstractPropertyOut(Component* owner)
        : ConnectionPipe(owner) {}

    AbstractPropertyOut() = delete;
    AbstractPropertyOut(const AbstractPropertyOut&) = delete;
    AbstractPropertyOut& operator=(const AbstractPropertyOut&) = delete;
    AbstractPropertyOut(AbstractPropertyOut&&) = delete;
    AbstractPropertyOut operator=(AbstractPropertyOut&&) = delete;
    virtual ~AbstractPropertyOut() = default;
};

class AbstractPropertyIn : public ConnectionPipe {
    friend class MessageManager;

public:
    AbstractPropertyIn(Component* owner)
        : ConnectionPipe(owner) {}

    AbstractPropertyIn() = delete;
    AbstractPropertyIn(const AbstractPropertyIn&) = delete;
    AbstractPropertyIn& operator=(const AbstractPropertyIn&) = delete;
    AbstractPropertyIn(AbstractPropertyIn&&) = delete;
    AbstractPropertyIn& operator=(AbstractPropertyIn&&) = delete;
    virtual ~AbstractPropertyIn() = default;

protected:
    virtual void RemoveSource() = 0;
};


/***************
 *   Message   *
 ***************/

class AbstractMessageOut : public ConnectionPipe {
    friend class MessageManager;

public:
    AbstractMessageOut(Component* owner)
        : ConnectionPipe(owner) {}

    AbstractMessageOut() = delete;
    AbstractMessageOut(const AbstractMessageOut&) = delete;
    AbstractMessageOut& operator=(const AbstractMessageOut&) = delete;
    AbstractMessageOut(AbstractMessageOut&&) = delete;
    AbstractMessageOut operator=(AbstractMessageOut&&) = delete;
    virtual ~AbstractMessageOut() = default;
};

class AbstractMessageIn : public ConnectionPipe {
    friend class MessageManager;

public:
    AbstractMessageIn(Component* owner)
        : ConnectionPipe(owner) {}

    AbstractMessageIn() = delete;
    AbstractMessageIn(const AbstractMessageIn&) = delete;
    AbstractMessageIn& operator=(const AbstractMessageIn&) = delete;
    AbstractMessageIn(AbstractMessageIn&&) = delete;
    AbstractMessageIn& operator=(AbstractMessageIn&&) = delete;
    virtual ~AbstractMessageIn() = default;

protected:
    virtual void Receive(void* message) = 0;
};


/*************
 *  Trigger  *
 *************/

class AbstractTriggerOut : ConnectionPipe {
    friend class MessageManager;

public:
    AbstractTriggerOut(Component* owner)
        : ConnectionPipe(owner) {}

    AbstractTriggerOut() = delete;
    AbstractTriggerOut(const AbstractTriggerOut&) = delete;
    AbstractTriggerOut& operator=(const AbstractTriggerOut&) = delete;
    AbstractTriggerOut(AbstractTriggerOut&&) = delete;
    AbstractTriggerOut& operator=(AbstractTriggerOut&&) = delete;
    virtual ~AbstractTriggerOut() = default;
};

class AbstractTriggerIn : ConnectionPipe {
    friend class MessageManager;

public:
    AbstractTriggerIn(Component* owner)
        : ConnectionPipe(owner) {}

    AbstractTriggerIn() = delete;
    AbstractTriggerIn(const AbstractTriggerIn&) = delete;
    AbstractTriggerIn& operator=(const AbstractTriggerIn&) = delete;
    AbstractTriggerIn(AbstractTriggerIn&&) = delete;
    AbstractTriggerIn& operator=(AbstractTriggerIn&&) = delete;
    virtual ~AbstractTriggerIn() = default;

protected:
    virtual void Receive() = 0;
};

#endif
