#ifndef PropertyIn_h
#define PropertyIn_h

#include "MessageManager.h"
#include "PropertyOut.h"

template <class T>
class PropertyIn : public IPropertyIn {
    friend class MessageManager;

public:
    PropertyIn(Component* owner)
        : IPropertyIn(owner)
        , m_Source(nullptr) {}

    const T& Value() const { return m_Source->Value(); }
    operator const T&() const { return m_Source->Value(); }

    bool Connected() const { return m_Source != nullptr; }

private:
    void RemoveSource() override { m_Source = nullptr; }

    PropertyOut<T>* m_Source;
};

#endif
