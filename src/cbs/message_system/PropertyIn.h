#ifndef PropertyIn_h
#define PropertyIn_h

#include "MessageManager.h"
#include "PropertyOut.h"

template <class T>
class PropertyIn : public IPropertyIn {
    friend class MessageManager;

public:
    PropertyIn(IComponent* owner)
        : IPropertyIn(owner)
        , m_Source(nullptr) {
    }

    PropertyIn(PropertyIn&& other) = default;

    T& Value() const { return *m_Source; }
    operator const T&() const { return *m_Source; }

    bool Connected() const { return m_Source != nullptr; }

private:
    void Reset() override {
        m_Source = nullptr;
    }

    PropertyOut<T>* m_Source;
};

#endif
