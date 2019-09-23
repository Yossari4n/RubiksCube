#ifndef PropertyIn_h
#define PropertyIn_h

#include "MessageManager.h"
#include "PropertyOut.h"

template <class T>
class PropertyIn final : public AbstractPropertyIn {
    friend class MessageManager;

public:
    PropertyIn()
        : m_Owner(nullptr)
        , m_Source(nullptr) { }
    ~PropertyIn() = default;

    Component* Owner() const override { return m_Owner; }

    const T& Value() const { return m_Source->Value(); }
    operator const T&() const { return m_Source->Value(); }

    bool Connected() const { return m_Source != nullptr; }

private:
    PropertyIn(Component* owner)
        : m_Owner(owner)
        , m_Source(nullptr) {}

    PropertyIn& operator=(const PropertyIn& other) {
        if (this == &other) {
            return *this;
        }

        m_Owner = other.m_Owner;
        m_Source = other.m_Source;

        return *this;
    }

    PropertyIn(const PropertyIn&) = default;
    PropertyIn(PropertyIn&&) = default;
    PropertyIn& operator=(PropertyIn&&) = default;

    void RemoveSource() override { m_Source = nullptr; }

    Component* m_Owner;
    PropertyOut<T>* m_Source;
};

#endif
