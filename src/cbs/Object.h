#ifndef Object_h
#define Object_h

#include "message_system/MessageManager.h"
#include "components/IComponent.h"
#include "components/Transform.h"

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

class ObjectManager;
class IScene;

class Object {
    using Components_t = std::vector<std::unique_ptr<IComponent>>;

public:
    Object(ObjectManager& scene, std::uint8_t id, std::string name = "object");
    Object(const Object& other, std::uint8_t id, std::string name = "");
    
    void ProcessFrame();

    void InitializeComponents();
    void UpdateComponents();
    void DestroyComponents();

    std::uint8_t ID() const { return m_ID; }

    const std::string& Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }

    IScene& Scene() const;
    Transform& Root() { return m_Root; }


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


    /**
     * Connect
     *
     * TODO doc
     */
    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
        assert(subject.Owner()->Object().ID() == observer.Owner()->Object().ID());
        m_MessageManager.Connect(subject, observer);
    }

    template <class M, class O, void(O::* F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == receiver.Owner()->Object().ID());
        m_MessageManager.Connect(sender, receiver);
    }


    /**
     * Disconnect
     *
     * TODO doc
     */
    template <class T>
    void Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
        assert(subject.Owner()->Object().ID() == observer.Owner()->Object().ID());
        m_MessageManager.Disconnect(subject, observer);
    }

    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == receiver.Owner()->Object().ID());
        m_MessageManager.Disconnect(sender, receiver);
    }

private:
    void MarkToDestroy(Components_t::iterator it);

    std::uint8_t m_ID;
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
