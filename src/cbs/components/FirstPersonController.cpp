#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(float movement_speed_fast, float movement_speed_slow, float mouse_sensivity)
    : m_CurrentMovementSpeed(0.0f)
    , m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensitivity(mouse_sensivity)
    , m_VerticalRotation(0.0f)
    , m_LastMousePos(0.0f) {
}

void FirstPersonController::Initialize() {
    // TODO store original rotation from Transform component
    m_LastMousePos = g_Input.MousePosition();

    RegisterUpdateCall();
}

void FirstPersonController::Update() {
    // Mouse
    float rot_ver = glm::radians(g_Input.MouseOffset().y * m_MouseSensitivity);
    float rot_hor = glm::radians(-g_Input.MouseOffset().x * m_MouseSensitivity);
    m_VerticalRotation += rot_ver;

    // Prevent object flip
    if (m_VerticalRotation > DEGREES_60) {
        m_VerticalRotation = DEGREES_60;
        rot_ver = 0.0f;
    } else if (m_VerticalRotation < -DEGREES_60) {
        m_VerticalRotation = -DEGREES_60;
        rot_ver = 0.0f;
    }

    // Update vectors
    Object().Root().Rotate(glm::vec3(0.0f, rot_hor, 0.0f));
    Object().Root().RotateRelative(glm::vec3(0.0f, 0.0f, rot_ver));

    // Keyboard
    if (g_Input.KeyState(GLFW_KEY_LEFT_SHIFT) || g_Input.KeyState(GLFW_KEY_RIGHT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }

    glm::vec3 movement(0.0f);
    if (g_Input.KeyHold(GLFW_KEY_UP)) {
        movement.x = m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }
    if (g_Input.KeyHold(GLFW_KEY_DOWN)) {
        movement.x = -m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }
    if (g_Input.KeyHold(GLFW_KEY_LEFT)) {
        movement.z = -m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }
    if (g_Input.KeyHold(GLFW_KEY_RIGHT)) {
        movement.z = m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }

    Object().Root().MoveRelative(movement);
}
