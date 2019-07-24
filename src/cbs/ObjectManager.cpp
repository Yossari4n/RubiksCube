#include "ObjectManager.h"

#include "../scenes/IScene.h"

ObjectManager::ObjectManager(IScene& owner)
    : m_Scene(owner)
    , m_NextObjectID(0)
    , m_ToInitialize(0)
    , m_ToInitializeNextFrame(0) 
    , m_ToDestroy(0) {
}

void ObjectManager::ProcessFrame() {
    InitializeObjects();
    UpdateObjects();
    DestroyObjects();
}

void ObjectManager::InitializeObjects() {
    m_ToInitialize = m_ToInitializeNextFrame;
    m_ToInitializeNextFrame = 0;
    for (Objects_t::size_type i = 0; i < m_ToInitialize; i++) {
        m_Objects[m_Objects.size() - 1 - i - m_ToInitializeNextFrame]->InitializeComponents();
    }
    m_ToInitialize = 0;
}

void ObjectManager::UpdateObjects() {
    for (Objects_t::size_type i = m_ToInitializeNextFrame; i < m_Objects.size() - m_ToInitializeNextFrame - m_ToDestroy; i++) {
        m_Objects[m_Objects.size() - 1 - i - m_ToInitializeNextFrame]->ProcessFrame();
    }
}

void ObjectManager::DestroyObjects() {
    if (m_ToDestroy > 0) {
        for (Objects_t::size_type i = 0; i < m_ToDestroy; i++) {
            m_Objects[m_Objects.size() - 1 - i - m_ToInitializeNextFrame]->DestroyComponents();
        }
        m_Objects.erase(m_Objects.begin(), m_Objects.begin() + m_ToDestroy);
        m_ToDestroy = 0;
    }
}

Object* ObjectManager::CreateObject(std::string name) {
    m_Objects.push_back(std::make_unique<Object>(*this, m_NextObjectID, name));

    m_ToInitializeNextFrame = m_ToInitializeNextFrame + 1;

    m_NextObjectID = m_NextObjectID + 1;

    return m_Objects.at(m_Objects.size() - 1).get();
}

Object* ObjectManager::CreateObject(const Object* other, std::string name) {
    m_Objects.push_back(std::make_unique<Object>(*other, m_NextObjectID, name));

    m_ToInitializeNextFrame = m_ToInitializeNextFrame + 1;

    m_NextObjectID = m_NextObjectID + 1;
    
    return m_Objects.at(m_Objects.size() - 1).get();
}

void ObjectManager::DestroyObject(std::uint8_t id) {
    auto object = std::find_if(m_Objects.begin(),
                               m_Objects.end(),
                               [=](std::unique_ptr<Object>& obj) { return obj->ID() == id; });

    if (object != m_Objects.end()) {
        MarkToDestroy(object);
    }
}

void ObjectManager::MarkToDestroy(Objects_t::iterator it) {
    // Check if object hasn't been already marked
    if (std::distance(it, m_Objects.begin()) > static_cast<ptrdiff_t>(m_ToDestroy)) {
        m_ToDestroy = m_ToDestroy + 1;
        std::iter_swap(m_Objects.begin() + m_ToDestroy, it);
    }
}
