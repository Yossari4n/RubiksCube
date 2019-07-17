#ifndef Object_h
#define Object_h

#include "Transform.h"
#include "components/IComponent.h"
#include "../scenes/IScene.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#pragma warning(pop)

#include <string>
#include <vector>
#include <algorithm>

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
        auto comp = new T(params...);
        comp->m_Object = this;
        
        // Register IComponent in a pool
        m_Components.push_back(comp);

        // Return pointer of T type
        return comp;
    }
    
    template <class T>
    T* CreateComponent(T* other) {
        // Create new IComponent by invoking copy constructor
        auto comp = new T(*other);
        comp->m_Object = this;
        
        // Register IComponent in a pool
        m_Components.push_back(comp);
        
        // Return pointer of T type
        return comp;
    }
    
    template <class T>
    void RemoveComponent() {
        // Find component to remove by linear search with casting
        m_Components.erase(std::remove_if(m_Components.begin(),
                                          m_Components.end(),
                                          [](IComponent* comp) {
                                              if (dynamic_cast<T*>(comp) != nullptr) {
                                                  comp->Destroy();
                                                  return true;
                                              }
                                              
                                              return false;
                                          }),
                           m_Components.end());
    }
    
    template <class T>
    T* GetComponent() {
        T* comp = nullptr;
        
        // Find component by linear search with casting
        auto it = m_Components.begin();
        while (it != m_Components.end() && comp == nullptr ) {
            comp = dynamic_cast<T*>(*it);
            
            it++;
        }
        
        return comp;
    }
    
    const std::string& Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }
    
    IScene& Scene() const { return m_Owner.Scene(); }
    Transform& Transform() { return m_Transform; }

private:
    std::string m_Name;
    
    ObjectManager& m_Owner;
    class Transform m_Transform;
    
    std::vector<IComponent*> m_Components;
};

#endif
