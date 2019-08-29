#ifndef PropertyOut_h
#define PropertyOut_h

#include "MessageManager.h"

template <class T>
class PropertyOut : public IPropertyOut {
    friend class MessageManager;

public:
    PropertyOut(Component* owner)
        : IPropertyOut(owner)
        , m_Value() {}

    template <class ...Args>
    PropertyOut(Component* owner, Args&& ... params)
        : IPropertyOut(owner)
        , m_Value(params...) {}

    T& operator=(const T& value) {
        m_Value = value;

        return m_Value;
    }

    T& Value() { return m_Value; }
    const T& Value() const { return m_Value; }

    operator T&() { return m_Value; }
    operator const T&() const { return m_Value; }

private:
    T m_Value;
};

#endif
