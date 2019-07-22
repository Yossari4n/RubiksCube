#include "Object.h"

Object::Object(ObjectManager& owner, std::string name)
    : m_Name(name)
    , m_Owner(owner)
    , m_NextCompID(2)
    , m_ToUpdateStart(0)
    , m_ToDestroyCount(0) {
    IComponent* root = &m_Root;
    root->m_Object = this;
    root->m_ID = 1;
}

Object::Object(const Object& other, std::string name)
    : m_Name(name.empty() ? other.Name() + "_copy" : name)
    , m_Owner(other.m_Owner)
    , m_Root(other.m_Root)
    , m_NextCompID(other.m_NextCompID)
    , m_ToUpdateStart(other.m_ToUpdateStart)
    , m_ToDestroyCount(other.m_ToDestroyCount) {

    // Copy root component
    IComponent* root = &m_Root;
    root->m_Object = this;

    // Copy components
    for (auto comp : other.m_Components) {
        m_Components.push_back(comp->Clone());
        m_Components[m_Components.size() - 1]->m_Object = this;
        m_Components[m_Components.size() - 1]->m_ID = comp->m_ID;
        m_Components[m_Components.size() - 1]->Initialize();
    }

    // Copy connections between components
    // TODO
}

Object::~Object() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        delete (*it);
    }
}

void Object::Initialize() {
    for (auto it = m_Components.begin(); it != m_Components.begin() + m_ToUpdateStart; it++) {
        (*it)->Initialize();
    }
    m_ToUpdateStart = 0;
}

void Object::Update() {
    for (auto it = m_Components.begin() + m_ToUpdateStart; it != m_Components.end() - m_ToDestroyCount; it++) {
        (*it)->Update();
    }
}

void Object::Destroy() {
    if (m_ToDestroyCount > 0) {
        for (auto it = m_Components.end() - m_ToDestroyCount; it != m_Components.end(); it++) {
            m_MessageManager.RemoveConnections(*it);
            (*it)->Destroy();
        }
        m_Components.erase(m_Components.end() - m_ToDestroyCount, m_Components.end());
        m_ToDestroyCount = 0;
    }
}

void Object::Disconnect(IMessageOut& sender, IMessageIn& receiver) {
    m_MessageManager.Disconnect(&sender, &receiver);
}

void Object::MarkToDestroy(std::vector<IComponent*>::iterator it) {
    if (std::distance(it, m_Components.end()) > m_ToDestroyCount) {
        m_ToDestroyCount = m_ToDestroyCount + 1;
        std::iter_swap(it, m_Components.end() - m_ToDestroyCount);
    }
}
