#ifndef Object_h
#define Object_h

#include "message_system/MessageManager.h"
#include "components/IComponent.h"
#include "components/Transform.h"
#include "../scenes/IScene.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#pragma warning(pop)

#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>

class Object {
    using Components_t = std::vector<std::unique_ptr<IComponent>>;

public:
    Object(ObjectManager& scene, std::string name = "object");
    Object(const Object& other, std::string name = "");
    
    void ProcessFrame();

    void InitializeComponents();
    void UpdateComponents();
    void DestroyComponents();
    
    /**
     * Create component
     *
     * TODO dock
     */
    template <class T, typename ...Args>
    T* CreateComponent(Args&&... params) {
        // Create new IComponent
        IComponent* comp = new T(params...);
        comp->m_Object = this;
        comp->m_ID = m_NextCompID;
        
        // Add new IComponent at the end of vecotr to be initialized in the next frame
        m_Components.emplace_back(comp);
        m_ToInitializeNextFrame = m_ToInitializeNextFrame + 1;

        m_NextCompID = m_NextCompID + 1;

        // Return pointer of T type
        return dynamic_cast<T*>(comp);
    }

    template <class T>
    T* CreateComponent(T* other) {
        // Create new IComponent by invoking copy constructor
        IComponent* comp = new T(*other);
        comp->m_Object = this;
        comp->m_ID = m_NextCompID;
        
        // Add new IComponent at the end of vecotr to be initialized in the next frame
        m_Components.emplace_back(comp);
        m_ToInitialize = m_ToInitialize + 1;

        m_NextCompID = m_NextCompID + 1;

        // Return pointer of T type
        return dynamic_cast<T*>(comp);
    }


    /**
     * Remove component(s)
     *
     * TODO dock
     */
    // TODO test
    template <class T>
    void RemoveComponent() {
        auto comp = std::find_if(m_Components.begin(),
                                 m_Components.end(),
                                 [](std::unique_ptr<IComponent>& comp) { return dynamic_cast<T*>(comp.get()) != nullptr; });

        if (comp != m_Components.end()) {
            MarkToDestroy(comp);
        }
    }

    // TODO test
    template <class T>
    void RemoveComponents() {
        std::vector<std::vector<IComponent>::iterator> to_remove;

        for (auto& comp : m_Components) {
            if (dynamic_cast<T*>(comp->get()) != nullptr) {
                MarkToDestroy(comp);
            }
        }
    }
    
    // TODO test
    void RemoveComponent(std::uint8_t id) {
        assert(id > 1);
        
        auto comp = std::find_if(m_Components.begin(),
                                 m_Components.end(),
                                 [=](std::unique_ptr<IComponent>& comp) { return comp->ID() == id; });

        if (comp != m_Components.end()) {
            MarkToDestroy(comp);
        }
    }


    /**
     * Get component(s)
     *
     * TODO dock
     */
    // TODO test
    template <class T>
    T* GetComponent() {
        T* comp = nullptr;

        auto it = m_Components.begin();
        while (it != m_Components.end() && comp == nullptr ) {
            comp = dynamic_cast<T*>(*it);
            
            it++;
        }
 
        return comp;
    }

    // TODO test
    template <class T>
    std::vector<T*> GetComponents() {
        std::vector<T*> comps;
        T* comp = nullptr;

        auto it = m_Components.begin();
        while (it != m_Components.end()) {
            comp = dynamic_cast<T*>(*it);

            if (comp != nullptr) {
                comps.push_back(comp);
            }
        }

        return comps;
    }

    // TODO test
    template <class T>
    T* GetComponent(std::uint8_t id) {
        auto it = std::find_if(m_Components.begin(),
                               m_Components.end(),
                               [=](IComponent* comp) {
                                   if (comp->ID() == id) {
                                       comp->Destroy();
                                       return true;
                                   }
                                   return false;
                               });
        return dynamic_cast<T*>(*it);
    }


    const std::string& Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }
    
    IScene& Scene() const { return m_Owner.Scene(); }
    Transform& Root() { return m_Root; }

    template<class M, class T, void(T::* F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, T, F>& receiver) {
        m_MessageManager.Connect(sender, receiver);
    }

    void Disconnect(IMessageOut& sender, IMessageIn& receiver);

private:
    void MarkToDestroy(Components_t::iterator it);

    std::string m_Name;
    
    ObjectManager& m_Owner;
    MessageManager m_MessageManager;

    Transform m_Root;

    std::uint8_t m_NextCompID;
    // [ToDestroy_1, ..., ToDestroy_i, ToUpdate_1, ..., ToUpdate_j, ToInit_1, ..., ToInit_k]
    Components_t m_Components;
    Components_t::size_type m_ToInitialize;
    Components_t::size_type m_ToInitializeNextFrame;
    Components_t::size_type m_ToDestroy;
};

#endif
