#ifndef FirstPersonController_h
#define FirstPersonController_h

#include "IComponent.h"
#include "../Object.h"
#include "../message_system/PropertyIn.h"
#include "../../scenes/IScene.h"

#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

#define GLM_ENABLE_EXPERIMENTAL
#pragma warning(push, 0)
#include <glm/gtx/vector_angle.hpp>
#pragma warning(pop)

#include <iostream>

constexpr auto DEGREES_60 = (60.0f * 3.14f / 180.0f);

class FirstPersonController : public IComponent {
public:
    FirstPersonController(float movement_speed_fast = 50.0f, float movement_speed_slow = 1.0f, float mouse_sensitivity = 0.1f);

    void Initialize() override;
    void Update() override;

private:
    float m_CurrentMovementSpeed;
    float m_MovementSpeedFast;
    float m_MovementSpeedSlow;
    float m_MouseSensitivity;
    float m_VerticalRotation;
    
    glm::vec2 m_LastMousePos;
};

#endif
