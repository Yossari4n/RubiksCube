#ifndef PropertyOut_h
#define PropertyOut_h

#include "MessageManager.h"


template <class T>
class PropertyOut final : public AbstractPropertyOut {
    friend class MessageManager;

public:
    PropertyOut()
        : m_Owner(nullptr) {}
    ~PropertyOut() = default;

    Component* Owner() const override { return m_Owner; }

    T& operator=(const T& value) { return (*m_Value = value); }

    T& Value() { return *m_Value; }
    const T& Value() const { return *m_Value; }

    operator T&() { return *m_Value; }
    operator const T&() const { return *m_Value; }

private:
    PropertyOut(Component* owner)
        : m_Owner(owner) {
        m_Value = std::make_unique<T>();
    }

    template <class ...Args>
    PropertyOut(Component* owner, Args&& ...params)
        : m_Owner(owner) {
        m_Value = std::make_unique<T>(params...);
    }

    PropertyOut& operator=(const PropertyOut& other) {
        if (this == &other) {
            return *this;
        }

        m_Owner = other.m_Owner;
        m_Value = std::make_unique<T>(*other.m_Value.get());

        return *this;
    }

    PropertyOut(const PropertyOut&) = default;
    PropertyOut(PropertyOut&&) = default;
    PropertyOut& operator=(PropertyOut&&) = default;

    Component* m_Owner;
    std::unique_ptr<T> m_Value;
};

#endif
