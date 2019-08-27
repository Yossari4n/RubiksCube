#ifndef ObjectManager_h
#define ObjectManager_h

#include "Object.h"

#include <vector>
#include <string>

class Scene;

class ObjectManager {
    using Objects_t = std::vector<std::unique_ptr<Object>>;

public:
    explicit ObjectManager(class Scene& owner);

    void ProcessFrame();

    void InitializeObjects();
    void UpdateObjects();
    void DestroyObjects();
    
    Object* CreateObject(std::string name = "");
    void DestroyObject(std::uint8_t id);
    
    Scene& Scene() const { return m_Scene; }
    
private:
    void MarkToDestroy(Objects_t::iterator it);

    class Scene& m_Scene;

    std::uint8_t m_NextObjectID;
    Objects_t m_Objects;
    Objects_t::size_type m_ToInitialize;
    Objects_t::size_type m_ToInitializeNextFrame;
    Objects_t::size_type m_ToDestroy;
};

#endif
