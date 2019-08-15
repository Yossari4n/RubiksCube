#include "IScene.h"

#include "../rendering/IDrawable.h"
#include "../rendering/ILightSource.h"

IScene::IScene()
    : m_ObjectManager(*this)
    , m_DrawManager()
    , m_Running(true)
    , m_FrameRateLimit(0.0f) {
}

void IScene::PreRun() {
    m_Running = true;
    
    m_DrawManager.Initialize();
    m_ObjectManager.InitializeObjects();
}

void IScene::Run() {
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

void IScene::PostRun() {
    m_ObjectManager.DestroyObjects();
}

void IScene::Exit() {
    m_Running = false;
}

void IScene::FrameRateLimit(unsigned int frame_rate) {
    m_FrameRateLimit = frame_rate != 0 ? 1.0f / (float)frame_rate : 0.0f;
}

Object* IScene::CreateObject(std::string name) {
    return m_ObjectManager.CreateObject(name);
}

Object* IScene::CreateObject(const Object* other, std::string name) {
    return m_ObjectManager.CreateObject(other, name);
}

void IScene::DestroyObject(std::uint8_t id) {
    m_ObjectManager.DestroyObject(id);
}

void IScene::RegisterDrawCall(IDrawable* drawable) {
    m_DrawManager.RegisterDrawCall(drawable);
}

void IScene::UnregisterDrawCall(IDrawable* drawable) {
    m_DrawManager.UnregisterDrawCall(drawable);
}

void IScene::RegisterWidget(IWidget* widget) {
    m_DrawManager.RegisterWidget(widget);
}

void IScene::UnregisterWidget(IWidget* widget) {
    m_DrawManager.UnregisterWidget(widget);
}

void IScene::RegisterLightSource(ILightSource* light_source) {
    m_DrawManager.RegisterLightSource(light_source);
}

void IScene::UnregisterLightSource(ILightSource* light_source) {
    m_DrawManager.UnregisterLightSource(light_source);
}

void IScene::RegisterCamera(Camera* camera) {
    m_DrawManager.RegisterCamera(camera);
}

Camera* IScene::MainCamera() const {
    return m_DrawManager.MainCamera();
}

void IScene::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_DrawManager.Skybox(right, left, top, bottom, back, front);
}

void IScene::Background(const glm::vec3& background) {
    m_DrawManager.Background(background);
}
