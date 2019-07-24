#ifndef PropertyOut_h
#define PropertyOut_h

#include "MessageManager.h"

template <class T>
class PropertyOut : public IPropertyOut {
    friend class MessageManager;

public:
    PropertyOut() = default;

    PropertyOut(IComponent* owner)
        : IPropertyOut(owner)
        , m_Value() {
    }

    PropertyOut(IComponent* owner, const T& value)
        : IPropertyOut(owner)
        , m_Value(value) {
    }

    T& operator=(const T& value) {
        m_Value = value;

        return m_Value;
    }

    operator T&() { return m_Value;  }

private:
    T m_Value;
};

#endif
