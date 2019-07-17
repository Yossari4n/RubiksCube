#ifndef DrawManager_h
#define DrawManager_h

#include "ShaderProgram.h"
#include "Cubemap.h"

#include <vector>
#include <array>
#include <assert.h>

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

class Camera;
class IDrawable;
class ILightSource;

class DrawManager {
public:
    DrawManager();

    void Initialize();
    
    void RegisterCamera(Camera* camera);
    Camera* MainCamera() const;
    
    void Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void Background(const glm::vec3& background);
    
    void RegisterDrawCall(IDrawable* component);
    void UnregisterDrawCall(IDrawable* component);
    
    void RegisterLightSource(ILightSource* light_source);
    void UnregisterLightSource(ILightSource* light_source);
    
    void CallDraws() const;
    
private:
    glm::vec3 m_Background;
    std::unique_ptr<Cubemap> m_Skybox;
    
    Camera* m_Camera;
    std::vector<IDrawable*> m_Drawables;
    std::vector<ILightSource*> m_LightSources;
    
    std::array<ShaderProgram, static_cast<size_t>(ShaderProgram::Type::COUNT)> m_ShaderPrograms;
};

#endif
