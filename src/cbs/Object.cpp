#include "Object.h"

Object::Object(ObjectManager& owner, std::string name)
    : m_Name(name)
    , m_Owner(owner)
    , m_NextCompID(2)
    , m_Root() {
    IComponent* root = &m_Root;
    root->m_Object = this;
    root->m_ID = 1;
}

Object::Object(const Object& other, std::string name)
    : m_Name(name.empty() ? other.Name() + "_copy" : name)
    , m_Owner(other.m_Owner)
    , m_MessageManager(1)
    , m_Root(other.m_Root)
    , m_NextCompID(other.m_NextCompID) {
    
    // Copy root component
    IComponent* root = &m_Root;
    root->m_Object = this;

    // Copy components
    for (auto it = other.m_Components.begin(); it != other.m_Components.end(); ++it) {
        m_Components.push_back((*it)->Clone());
        m_Components[m_Components.size() - 1]->m_Object = this;
        m_Components[m_Components.size() - 1]->m_ID = (*it)->m_ID;
        m_Components[m_Components.size() - 1]->Initialize();
    }
}

Object::~Object() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        delete (*it);
    }
}

void Object::Initialize() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        (*it)->Initialize();
    }
}

void Object::Update() {
    // To prevent premature destruction of components deleted in update
    // this loop can't use iterators
    for (auto&& comp : m_Components) {
        comp->Update();
    }
}

void Object::Destroy() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        (*it)->Destroy();
    }
}

Transform& Object::Root() {
    return m_Root;
}
