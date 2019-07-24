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

    operator T&() { return *m_Source; }

private:
    PropertyOut<T>* m_Source;
};

#endif
