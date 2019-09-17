#ifndef Object_h
#define Object_h

#include "message_system/MessageManager.h"
#include "components/Component.h"
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
class Scene;

class Object {
    using Components_t = std::vector<std::unique_ptr<Component>>;

public:
    Object(ObjectManager& scene, std::uint8_t id, std::string name = "object");

    void ProcessFrame();

    void InitializeComponents();
    void UpdateComponents();
    void DestroyComponents();

    void RegisterUpdateCall(const Component* component);
    void UnregisterUpdateCall(const Component* component);

    std::uint8_t ID() const { return m_ID; }

    const std::string& Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }

    Scene& Scene() const;
    Transform& Root() { return m_Root; }


    /**
     * Create component
     *
     * Creates component of type T with arguments Args and returns pointer of type T.
     * Object passes reference to itself as first argument.
     * Futhermore component receives it's own ID greater than 0.
     * By default Transform component is marked as Root and has ID of 1.
     * New components are guarantee to be initialized at the begining of a next frame.
     */
    template <class T, typename ...Args>
    T* CreateComponent(Args&&... params) {
        // Add new Component at the end of vecotr to be initialized in the next frame
        m_Components.emplace_back(std::make_unique<T>(params...));
        m_Components.back()->m_Object = this;
        m_Components.back()->m_ID = m_NextCompID;

        m_ToInitializeNextFrame = m_ToInitializeNextFrame + 1;
        m_NextCompID = m_NextCompID + 1;

        // Return pointer of T type
        return dynamic_cast<T*>(m_Components.back().get());
    }


    /**
     * Remove component(s)
     *
     * Mark component as to destroy and guarantees thier's Destory functions
     * will be called at the end of current frame. Destruction of object will
     * happen naturally after that.
     * Components to destory can be specified either by type or by ID. If type
     * is specified all components of this type will be destroyed.
     * Transform component by default cannot to be destroyed manually as it's
     * lifetime is bounded to Object lifetime.
     * Attempt to destroy non existing component will not have effect.
     */
    template <class T>
    void RemoveComponents() {
        std::vector<std::vector<Component>::iterator> to_remove;

        for (auto& comp : m_Components) {
            if (dynamic_cast<T*>(comp->get()) != nullptr) {
                MarkToDestroy(comp);
            }
        }
    }

    void RemoveComponent(std::uint8_t id) {
        assert(id > 1);
        
        auto comp = std::find_if(m_Components.begin(),
                                 m_Components.end(),
                                 [=](std::unique_ptr<Component>& comp) { return comp->ID() == id; });

        if (comp != m_Components.end()) {
            MarkToDestroy(comp);
        }
    }


    /**
     * Get component(s)
     *
     * Attempts to find components either by ID or by type.
     * Returns pointer, or vector of pointers if ID has not been specified,
     * of given type T. If no components found return nullptr or vector of size 0.
     */
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
        Components_t::iterator it = std::find_if(m_Components.begin(),
                               m_Components.end(),
                               [=](std::unique_ptr<Component>& curr) { return curr->ID() == id; });

        if (it != m_Components.end()) {
            return dynamic_cast<T*>(it->get());
        } else {
            return nullptr;
        }
    }


    /**
     * Connect
     *
     * Attempts to connect either properties, message or trigger pipes between two
     * owned components. Type compatibility is ensured at the compilation time.
     */
    template <class T>
    void Connect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
        assert(subject.Owner()->Object().ID() == m_ID && observer.Owner()->Object().ID() == m_ID);
        m_MessageManager.Connect(subject, observer);
    }

    template <class M, class O, void(O::* F)(M)>
    void Connect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_MessageManager.Connect(sender, receiver);
    }

    template <class O, void(O::*F)(void)>
    void Connect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_MessageManager.Connect(sender, receiver);
    }


    /**
     * Disconnect
     *
     * Attempts to disconnect either properties or message pipes of it's
     * two owned components. Type compatibility is ensured at the compilation time.
     */
    template <class T>
    void Disconnect(PropertyOut<T>& subject, PropertyIn<T>& observer) {
        assert(subject.Owner()->Object().ID() == m_ID && observer.Owner()->Object().ID() == m_ID);
        m_MessageManager.Disconnect(subject, observer);
    }

    template <class M, class O, void (O::*F)(M)>
    void Disconnect(MessageOut<M>& sender, MessageIn<M, O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_MessageManager.Disconnect(sender, receiver);
    }

    template <class O, void (O::*F)(void)>
    void Disconnect(TriggerOut& sender, TriggerIn<O, F>& receiver) {
        assert(sender.Owner()->Object().ID() == m_ID && receiver.Owner()->Object().ID() == m_ID);
        m_MessageManager.Disconnect(sender, receiver);
    }

private:
    void MarkToDestroy(Components_t::iterator it);

    std::uint8_t m_ID;
    std::string m_Name;

    ObjectManager& m_Owner;
    MessageManager m_MessageManager;

    std::uint8_t m_NextCompID;

    // All components owned by Object
    Transform m_Root;
    Components_t m_Components;
    Components_t::size_type m_CurrentIndex;
    // Components are divided into three different parts
    Components_t::size_type m_ToDestroy;                // Number of components at the begining to be destroyed
    Components_t::size_type m_ToUpdate;                 // Number of components in the middle to be updated with additional components not marked as to update till the ToInitialize sections
    Components_t::size_type m_ToInitialize;             // Number of components at the end to be initialized
    Components_t::size_type m_ToInitializeNextFrame;    // Number of components waiting to be initialized
};

#endif
