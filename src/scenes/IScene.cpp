#include "IScene.h"

#include "../rendering/IDrawable.h"
#include "../rendering/ILightSource.h"

Scene::Scene()
    : m_ObjectManager(*this)
    , m_Running(false)
    , m_FrameRateLimit(0.0f) {
}

void Scene::PreRun() {
    m_Running = true;
    m_DrawManager.Initialize();
}

void Scene::Run() {
    m_ObjectManager.InitializeObjects();

    // Initialize Time manager as close to game loop as possible
    // to avoid misrepresented delta time
    g_Time.Initialize();
    
    // Game loop
    while (m_Running && !glfwWindowShouldClose(g_Window)) {
        // If frame rate is greater than limit then wait
        do {
            g_Time.Hold();
            glfwPollEvents();
        } while (g_Time.DeltaTime() < m_FrameRateLimit);
        
        // Update global systems
        g_Time.Update();
        g_Input.Update(g_Window);
        
        // Managers
        m_ObjectManager.ProcessFrame();
        m_DrawManager.CallDraws();
    }
}

void Scene::PostRun() {
    m_ObjectManager.DestroyObjects();
}

void Scene::Exit() {
    m_Running = false;
}

void Scene::FrameRateLimit(unsigned int frame_rate) {
    m_FrameRateLimit = frame_rate != 0 ? 1.0f / (float)frame_rate : 0.0f;
}

Object* Scene::CreateObject(std::string name) {
    return m_ObjectManager.CreateObject(name);
}

void Scene::DestroyObject(std::uint8_t id) {
    m_ObjectManager.DestroyObject(id);
}

void Scene::RegisterDrawCall(IDrawable* drawable) {
    m_DrawManager.RegisterDrawCall(drawable);
}

void Scene::UnregisterDrawCall(IDrawable* drawable) {
    m_DrawManager.UnregisterDrawCall(drawable);
}

void Scene::RegisterWidget(IWidget* widget) {
    m_DrawManager.RegisterWidget(widget);
}

void Scene::UnregisterWidget(IWidget* widget) {
    m_DrawManager.UnregisterWidget(widget);
}

void Scene::RegisterLightSource(ILightSource* light_source) {
    m_DrawManager.RegisterLightSource(light_source);
}

void Scene::UnregisterLightSource(ILightSource* light_source) {
    m_DrawManager.UnregisterLightSource(light_source);
}

void Scene::RegisterCamera(Camera* camera) {
    m_DrawManager.RegisterCamera(camera);
}

Camera* Scene::MainCamera() const {
    return m_DrawManager.MainCamera();
}

void Scene::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_DrawManager.Skybox(right, left, top, bottom, back, front);
}

void Scene::Background(const glm::vec3& background) {
    m_DrawManager.Background(background);
}
