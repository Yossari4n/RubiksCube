#ifndef PropertyOut_h
#define PropertyOut_h

#include "MessageManager.h"

template <class T>
class PropertyOut : public IPropertyOut {
    friend class MessageManager;

public:
    PropertyOut(IComponent* owner)
        : IPropertyOut(owner)
        , m_Value() {}
    
    PropertyOut(IComponent* owner, const T& value)
        : IPropertyOut(owner)
        , m_Value(value) {}

    template <class ...Args>
    PropertyOut(IComponent* owner, Args&& ... params)
        : IPropertyOut(owner)
        , m_Value(params...) {}

    PropertyOut(IComponent* owner, const PropertyOut<T>& other)
        : IPropertyOut(owner)
        , m_Value(other.m_Value) {}

    PropertyOut(PropertyOut&& other) = default;

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
