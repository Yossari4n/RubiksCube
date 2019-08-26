#include "Object.h"

#include "ObjectManager.h"
#include "../scenes/IScene.h"

Object::Object(ObjectManager& owner, std::uint8_t id, std::string name)
    : m_ID(id)
    , m_Name(name)
    , m_Owner(owner)
    , m_NextCompID(2)
    , m_CurrentIndex(0)
    , m_ToInitialize(0)
    , m_ToInitializeNextFrame(0)
    , m_ToUpdate(0)
    , m_ToDestroy(0) {
    IComponent* root = &m_Root;
    root->m_Object = this;
    root->m_ID = 1;
}

Object::Object(const Object& other, std::uint8_t id, std::string name)
    : m_ID(id)
    , m_Name(name.empty() ? other.Name() + "_copy" : name)
    , m_Owner(other.m_Owner)
    , m_Root(other.m_Root)
    , m_NextCompID(other.m_NextCompID)
    , m_CurrentIndex(other.m_CurrentIndex)
    , m_ToInitialize(other.m_ToInitialize)
    , m_ToInitializeNextFrame(other.m_ToInitializeNextFrame)
    , m_ToUpdate(other.m_ToUpdate)
    , m_ToDestroy(other.m_ToDestroy) {

    // Copy root component
    IComponent* root = &m_Root;
    root->m_Object = this;

    // Copy components
    for (auto& comp : other.m_Components) {
        m_Components.emplace_back(comp->Clone());
        m_Components[m_Components.size() - 1]->m_Object = this;
        m_Components[m_Components.size() - 1]->m_ID = comp->m_ID;
        m_Components[m_Components.size() - 1]->Initialize();
    }

    // Copy connections between components
    // TODO
}

void Object::ProcessFrame() {
    InitializeComponents();
    UpdateComponents();
    DestroyComponents();
}

void Object::InitializeComponents() {
    // Components registered in previous frame will be initialized now
    m_ToInitialize = m_ToInitializeNextFrame;
    m_ToInitializeNextFrame = 0;

    // Initialize all components from (end - m_ToInitialize - m_ToInitializeNextFrame) to (end - m_ToInitializeNextFrame)
    for (int i = 0; i < m_ToInitialize; i++) {
        m_Components[m_Components.size() - m_ToInitialize - m_ToInitializeNextFrame + i]->Initialize();
    }

    m_ToInitialize = 0;
}

void Object::UpdateComponents() {    
    // Update all components from (begin + m_ToDestroy + m_ToUpdate) to (begin + m_ToDestroy)
    for (int i = 0; i < m_ToUpdate; i++) {
        m_Components[m_ToDestroy + m_ToUpdate - i - 1]->Update();
    }
}

void Object::DestroyComponents() {
    // Destroy all components from begining to (begin + m_ToDestroy)
    if (m_ToDestroy > 0) {
        for (m_CurrentIndex = 0; m_CurrentIndex < m_ToDestroy; m_CurrentIndex++) {
            m_MessageManager.RemoveConnections(m_Components[m_Components.size() - 1 - m_CurrentIndex].get());
            m_Components[m_Components.size() - 1 - m_CurrentIndex - m_ToInitializeNextFrame]->Destroy();
        }
        m_Components.erase(m_Components.begin(), m_Components.begin() + m_ToDestroy);
        m_ToDestroy = 0;
    }
}

void Object::RegisterUpdateCall(const IComponent* component) {
    auto id = component->ID();
    Components_t::iterator comp = std::find_if(m_Components.begin(),
                                               m_Components.end(),
                                               [=](std::unique_ptr<IComponent>& curr) { return curr->ID() == id; });

    assert(comp != m_Components.end());
    if (std::distance(m_Components.begin() + m_ToDestroy, comp) >= static_cast<ptrdiff_t>(m_ToUpdate)) {
        m_CurrentIndex = m_CurrentIndex - 1;
        m_ToUpdate = m_ToUpdate + 1;
        std::iter_swap(m_Components.begin() + m_ToDestroy + m_ToUpdate - 1, comp);
    }
}

void Object::UnregisterUpdateCall(const IComponent* component) {
    auto id = component->ID();
    Components_t::iterator comp = std::find_if(m_Components.begin(),
                                               m_Components.end(),
                                               [=](std::unique_ptr<IComponent>& curr) { return curr->ID() == id; });

    assert(comp != m_Components.end());
    if (std::distance(m_Components.begin() + m_ToDestroy, comp) <= static_cast<ptrdiff_t>(m_ToUpdate)) {
        m_ToUpdate = m_ToUpdate - 1;
        std::iter_swap(m_Components.begin() + m_ToDestroy + m_ToUpdate, comp);
    }
}

IScene& Object::Scene() const {
    return m_Owner.Scene();
}

void Object::MarkToDestroy(Components_t::iterator it) {
    // Check if component hasn't been already marked
    if (std::distance(m_Components.begin(), it) > static_cast<ptrdiff_t>(m_ToDestroy)) {
        UnregisterUpdateCall(it->get());

        m_ToDestroy = m_ToDestroy + 1;
        std::iter_swap(m_Components.begin() + m_ToDestroy, it);
    }
}
