#ifndef IComponent_h
#define IComponent_h

#include <iostream>
#include <cassert>
#include <exception>

class Object;

class IComponent {
    friend class Object;

public:
    IComponent()
        : m_Object(nullptr)
        , m_Active(true) {
    }
    
    virtual ~IComponent() {
    }
    
    virtual IComponent* Clone() const {
        std::cerr << "Attempted to create copy of Compononent not implementing Clone() function\n";
        return nullptr;
    }
    
    Object& Object() const {
        return *m_Object;
    }
    
    bool Active() const {
        return m_Active;
    }
    
    void Activate() {
        if (m_Active) {
            return;
        }

        m_Active = true;
        OnActivate();
    }
    
    void Deactivate() {
        if (!m_Active) {
            return;
        }

        m_Active = false;
        OnDeactivate();
    }

protected:
    virtual void Initialize() {};
    virtual void OnActivate() {};
    virtual void Update() {};
    virtual void OnDeactivate() {};
    virtual void Destroy() {};
    
    bool m_Active;

private:
    class Object* m_Object;
};

#include "../Object.h"

#endif
