#ifndef Scene_hpp
#define Scene_hpp

#include "../cbs/ObjectManager.h"
#include "../rendering/DrawManager.h"
#include "../utilities/Time.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(Scene&&) = delete;

    virtual void CreateScene() = 0;

    void PreRun();
    void Run();
    void PostRun();

    void Exit();
    void FrameRateLimit(unsigned int frame_rate);
    float FrameRate() const { return 1.0f / g_Time.DeltaTime(); }

    // ObjectManger functions
    Object* CreateObject(std::string name = "");
    void DestroyObject(std::uint8_t id);

    // DrawManager functions
    void RegisterDrawCall(Drawable* drawable);
    void UnregisterDrawCall(Drawable* drawable);
    void RegisterWidget(IWidget* widget);
    void UnregisterWidget(IWidget* widget);
    void RegisterLightSource(ILightSource* light_source);
    void UnregisterLightSource(ILightSource* light_source);
    void RegisterCamera(Camera* camera);
    Camera* MainCamera() const;
    void Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void Background(const glm::vec3& background);

private:
    ObjectManager m_ObjectManager{ *this };
    DrawManager m_DrawManager{ };

    bool m_Running{ false };
    float m_FrameRateLimit{ 0.0f };
};

#endif
