#ifndef ConnectionInterfaces_h
#define ConnectionInterfaces_h

#include "MessageManager.h"

/**
 * AbstractProperty
 *
 * TODO doc
 **/
class AbstractPropertyOut {
    friend class MessageManager;

public:
    AbstractPropertyOut() = default;
    AbstractPropertyOut(const AbstractPropertyOut&) = delete;
    AbstractPropertyOut& operator=(const AbstractPropertyOut&) = delete;
    AbstractPropertyOut(AbstractPropertyOut&&) = delete;
    AbstractPropertyOut& operator=(AbstractPropertyOut&&) = delete;
    virtual ~AbstractPropertyOut() = default;

    virtual Component* Owner() const = 0;
};

class AbstractPropertyIn {
    friend class MessageManager;

public:
    AbstractPropertyIn() = default;
    AbstractPropertyIn(const AbstractPropertyIn&) = delete;
    AbstractPropertyIn& operator=(const AbstractPropertyIn&) = delete;
    AbstractPropertyIn(AbstractPropertyIn&&) = delete;
    AbstractPropertyIn& operator=(AbstractPropertyIn&&) = delete;
    virtual ~AbstractPropertyIn() = default;

    virtual Component* Owner() const = 0;

protected:
    virtual void RemoveSource() = 0;
};


/**
 * AbstractMessager
 *
 * TODO doc
 **/
class AbstractMessageOut {
    friend class MessageManager;

public:
    AbstractMessageOut() = default;
    AbstractMessageOut(const AbstractMessageOut&) = delete;
    AbstractMessageOut& operator=(const AbstractMessageOut&) = delete;
    AbstractMessageOut(AbstractMessageOut&&) = delete;
    AbstractMessageOut& operator=(AbstractMessageOut&&) = delete;
    virtual ~AbstractMessageOut() = default;

    virtual Component* Owner() const = 0;
};

class AbstractMessageIn {
    friend class MessageManager;

public:
    AbstractMessageIn() = default;
    AbstractMessageIn(const AbstractMessageIn&) = delete;
    AbstractMessageIn& operator=(const AbstractMessageIn&) = delete;
    AbstractMessageIn(AbstractMessageIn&&) = delete;
    AbstractMessageIn& operator=(AbstractMessageIn&&) = delete;
    virtual ~AbstractMessageIn() = default;

    virtual Component* Owner() const = 0;

protected:
    virtual void Receive(void* message) = 0;
};


/**
 * AbstractTrigger
 *
 * TODO doc
 **/
class AbstractTriggerOut {
    friend class MessageManager;

public:
    AbstractTriggerOut() = default;
    AbstractTriggerOut(const AbstractTriggerOut&) = delete;
    AbstractTriggerOut& operator=(const AbstractTriggerOut&) = delete;
    AbstractTriggerOut(AbstractTriggerOut&&) = delete;
    AbstractTriggerOut& operator=(AbstractTriggerOut&&) = delete;
    virtual ~AbstractTriggerOut() = default;

    virtual Component* Owner() const = 0;
    virtual void Trigger() = 0;
};

class AbstractTriggerIn {
    friend class MessageManager;

public:
    AbstractTriggerIn() = default;
    AbstractTriggerIn(const AbstractTriggerIn&) = delete;
    AbstractTriggerIn& operator=(const AbstractTriggerIn&) = delete;
    AbstractTriggerIn(AbstractTriggerIn&&) = delete;
    AbstractTriggerIn& operator=(AbstractTriggerIn&&) = delete;
    virtual ~AbstractTriggerIn() = default;

    virtual Component* Owner() const = 0;

protected:
    virtual void Receive() = 0;
};

#endif
