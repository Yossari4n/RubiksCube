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
#include <type_traits>

class Object {
public:
    Object(ObjectManager& scene, std::string name = "object");
    Object(const Object& other, std::string name = "");
    ~Object();
    
    void Initialize();
    void Update();
    void Destroy();
    
    template <class T, typename ...Args>
    T* CreateComponent(Args&&... params) {
        // Create new IComponent
        IComponent* comp = new T(params...);
        comp->m_Object = this;
        comp->m_ID = m_NextCompID;
        
        // Register IComponent in a pool
        m_Components.push_back(comp);

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
        
        // Register IComponent in a pool
        m_Components.push_back(comp);

        m_NextCompID = m_NextCompID + 1;

        // Return pointer of T type
        return dynamic_cast<T*>(comp);
    }

    template <class T>
    void RemoveComponent() {
        auto comp = std::find_if(m_Components.begin(),
                                 m_Components.end(),
                                 [](IComponent* comp) { return dynamic_cast<T*>(comp) != nullptr; });

        if (comp != m_Components.end()) {
            m_MessageManager.RemoveConnections(*comp);
            // TODO move destroy logic to update loop
            (*comp)->Destroy();
            m_Components.erase(comp);
        }
    }

    template <class T>
    void RemoveComponents() {
        std::vector<std::vector<IComponent*>::iterator> to_remove;

        for (auto comp : m_Components) {
            if (dynamic_cast<T*>(comp) != nullptr) {
                to_remove.push_back(comp);
            }
        }

        for (auto& comp : to_remove) {
            m_MessageManager.RemoveConnections(*comp);
            // TODO move destroy logic to update loop
            (*comp)->Destroy();
            m_Components.erase(comp);
        }
    }
    
    void RemoveComponent(std::uint8_t id) {
        assert(id > 1);
        
        auto comp = std::find_if(m_Components.begin(),
                                 m_Components.end(),
                                 [=](IComponent* comp) { return comp->ID() == id; });

        if (comp != m_Components.end()) {
            m_MessageManager.RemoveConnections(*comp);
            // TODO move destroy logic to update loop
            (*comp)->Destroy();
            m_Components.erase(comp);
        }
    }

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
    Transform& Root();

    template<class M, class T, void(T::* F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, T, F>& receiver) {
        m_MessageManager.Connect(sender, receiver);
    }

    void Disconnect(IMessageOut& sender, IMessageIn& receiver);

private:
    std::string m_Name;
    
    ObjectManager& m_Owner;
    MessageManager m_MessageManager;

    Transform m_Root;

    std::uint8_t m_NextCompID;
    std::vector<IComponent*> m_Components;
/*
    std::vector<IComponent*>::iterator m_ToInitialize;
    std::vector<IComponent*>::iterator m_ToUpdate;
    std::vector<IComponent*>::iterator m_ToDestroy;
*/
};

#endif
