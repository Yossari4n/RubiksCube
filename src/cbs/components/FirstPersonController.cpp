#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(float movement_speed_fast, float movement_speed_slow, float mouse_sensivity)
    : m_CurrentMovementSpeed(0.0f)
    , m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensitivity(mouse_sensivity)
    , m_VerticalRotation(0.0f)
    , m_LastMousePos(0.0f) 
    , m_Transform(nullptr) {
    
}

void FirstPersonController::Initialize() {
    m_LastMousePos = g_Input.MousePosition();
    m_Transform = &Object().Transform();
}

void FirstPersonController::OnActivate() {
    glm::vec3 curr_front = Object().Transform().Front();
    glm::vec3 projected_front(curr_front.x, 0.0f, curr_front.z); // Front vector projected onto XY plane
    
    m_VerticalRotation = glm::angle(glm::normalize(curr_front), glm::normalize(projected_front));
    
    // Becouse glm::angle always returns positive value angle needs to be negated manually
    if (curr_front.y < 0.0f) {
        m_VerticalRotation = -m_VerticalRotation;
    }
}

void FirstPersonController::Update() {
    if (!m_Active) {
        return;
    }
    
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
    m_Transform->Rotate(glm::vec3(0.0f, rot_hor, 0.0f));
    m_Transform->RotateRelative(glm::vec3(0.0f, 0.0f, rot_ver));
    
    // Keyboard
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }
    
    glm::vec3 movement(0.0f);
    if (g_Input.GetKeyState(GLFW_KEY_W)) {
        movement.x = m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }
    if (g_Input.GetKeyState(GLFW_KEY_S)) {
        movement.x = -m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }
    if (g_Input.GetKeyState(GLFW_KEY_A)) {
        movement.z = -m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }
    if (g_Input.GetKeyState(GLFW_KEY_D)) {
        movement.z = m_CurrentMovementSpeed * g_Time.DeltaTime();;
    }
    
    m_Transform->MoveRelative(movement);
}
