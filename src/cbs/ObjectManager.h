#ifndef ObjectManager_h
#define ObjectManager_h

#include <vector>
#include <string>

class IScene;
class Object;

class ObjectManager {
public:
    ObjectManager(IScene& owner);
    ~ObjectManager();
    
    void InitializeObjects();
    void UpdateObjects();
    void DestroyObjects();
    
    Object* CreateObject(std::string name = "");
    Object* CreateObject(const Object* other, std::string name = "");
    
    IScene& Scene() const { return m_Scene; }
    
private:
    IScene& m_Scene;
    std::vector<Object*> m_Objects;
};

#endif
