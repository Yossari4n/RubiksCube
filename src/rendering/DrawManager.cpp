#include "DrawManager.h"

#include "IDrawable.h"
#include "ILightSource.h"
#include "../utilities/Window.h"
#include "../rendering/Cubemap.h"
#include "../cbs/components/Camera.h"

DrawManager::DrawManager()
    : m_Skybox(nullptr)
    , m_Camera(nullptr)
    , m_Background(0.0f, 0.0f, 0.0f) {
}

void DrawManager::Initialize() {
    // Create shader programs
    m_ShaderPrograms[ShaderProgram::Type::PURE_COLOR].AttachShaders("src/shaders/PURE_COLOR.vert",
                                                                    "src/shaders/PURE_COLOR.frag");
    
    
    m_ShaderPrograms[ShaderProgram::Type::PURE_TEXTURE].AttachShaders("src/shaders/PURE_TEXTURE.vert",
                                                                      "src/shaders/PURE_TEXTURE.frag");
    
    
    m_ShaderPrograms[ShaderProgram::Type::PHONG].AttachShaders("src/shaders/PHONG.vert",
                                                               "src/shaders/PHONG.frag");
    m_ShaderPrograms[ShaderProgram::Type::PHONG].Traits(ShaderProgram::Trait::LIGHT_RECEIVER);
    

    m_ShaderPrograms[ShaderProgram::Type::SKYBOX].AttachShaders("src/shaders/SKYBOX.vert",
                                                                "src/shaders/SKYBOX.frag");
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void DrawManager::RegisterCamera(Camera *camera) {
    m_Camera = camera;
}

Camera* DrawManager::MainCamera() const {
    return m_Camera;
}

void DrawManager::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_Skybox = std::make_unique<Cubemap>(right, left, top, bottom, back, front, ShaderProgram::Type::SKYBOX);
}

void DrawManager::Background(const glm::vec3& background) {
    m_Background = background;
}

void DrawManager::RegisterDrawCall(IDrawable* component) {
    // Ensure that every component is registered at most once
    assert(std::find(m_Drawables.begin(), m_Drawables.end(), component) == m_Drawables.end());
    
    m_Drawables.push_back(component);
}

void DrawManager::UnregisterDrawCall(IDrawable* component) {
    // Unregistering unregistered component has no effect
    auto to_erase = std::find(m_Drawables.begin(), m_Drawables.end(), component);
    if (to_erase != m_Drawables.end()) {
        m_Drawables.erase(to_erase);
    }
}

void DrawManager::RegisterLightSource(ILightSource* light_source) {
    // Ensure that every component is registered at most once
    assert(std::find(m_LightSources.begin(), m_LightSources.end(), light_source) == m_LightSources.end());

    m_LightSources.push_back(light_source);
}

void DrawManager::UnregisterLightSource(ILightSource* light_source) {
    // Unregistering unregistered component has no effect
    auto to_erase = std::find(m_LightSources.begin(), m_LightSources.end(), light_source);
    if (to_erase != m_LightSources.end()) {
        m_LightSources.erase(to_erase);
    }
}

void DrawManager::CallDraws() const {
    glClearColor(m_Background.x, m_Background.y, m_Background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 pv = m_Camera->Projection() * m_Camera->ViewMatrix();
    
    // Draw objects
    for (auto to_draw = m_Drawables.cbegin(); to_draw != m_Drawables.cend(); to_draw++) {
        int shader_type = (*to_draw)->ShaderType();
        const ShaderProgram& curr_shader = m_ShaderPrograms[shader_type];
        
        curr_shader.Use();
        curr_shader.Uniform("pv", pv);
        
        // For each trait in shader set corresponding properties 
        if (curr_shader.Traits() & ShaderProgram::Trait::LIGHT_RECEIVER) {
            curr_shader.Uniform("viewPos", m_Camera->Object().Transform().Position());
            curr_shader.Uniform("material.shininess", 32.0f);
            
            for (auto light_source = m_LightSources.begin(); light_source != m_LightSources.end(); ++light_source) {
                (*light_source)->SetLightProperties(curr_shader);
            }
        }
        
        (*to_draw)->Draw(curr_shader);
    }
    
    // Draw skybox
    if (m_Skybox != nullptr) {
        glDepthFunc(GL_LEQUAL);
        const ShaderProgram& skybox_shader = m_ShaderPrograms[ShaderProgram::Type::SKYBOX];
        
        skybox_shader.Use();
        skybox_shader.Uniform("pv", m_Camera->Projection() * glm::mat4(glm::mat3(m_Camera->ViewMatrix())));
        
        m_Skybox->Draw(skybox_shader);
        
        glDepthFunc(GL_LESS);
    }
    
    glfwSwapBuffers(g_Window);
}
