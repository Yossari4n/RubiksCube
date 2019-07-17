#ifndef IComponent_h
#define IComponent_h

#include <iostream>
#include <cassert>
#include <exception>

class Object;

class IComponent {
    // TODO doc about friendship and constructors
    friend class Object;

public:
    IComponent()
        : m_Object(nullptr)
        , m_ID(0) {

    }
    
    virtual ~IComponent() {}
    
    virtual IComponent* Clone() const {
        std::cerr << "Attempted to create copy of Compononent not implementing Clone() function\n";
        return nullptr;
    }
    
    Object& Object() const {
        return *m_Object;
    }
    
protected:
    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Destroy() {};

private:
    class Object* m_Object;
    std::uint8_t m_ID;
};

#include "../Object.h"

#endif
