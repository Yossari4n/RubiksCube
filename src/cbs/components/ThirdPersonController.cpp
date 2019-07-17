#include "ThirdPersonController.h"

ThirdPersonController::ThirdPersonController(class Object* target, float radius, float mouse_sensitivity)
    : m_Target(&target->Transform())
    , m_Radius(radius)
    , m_MouseSensitivity(mouse_sensitivity)
    , m_Front(1.0f, 0.0f, 0.0f)
    , m_RotationAxis(0.0f, 0.0f, 1.0f)
    , m_XRotation(0.0f)
    , m_YRotation(0.0f) {

}

void ThirdPersonController::Radius(float radius) {
    if (radius < 0.0f) {
        radius = 0.0f;
    }
    
    m_Radius = radius;
}

void ThirdPersonController::OnActivate() {
    m_XRotation = 0.0f;
    m_YRotation = 0.0f;
    m_Front = glm::vec3(1.0f, 0.0f, 0.0f);
    m_RotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
}

void ThirdPersonController::Update() {
    if (!m_Active) {
        return;
    }
    
    // Accumulate mouse movement as rotations
    m_XRotation += -glm::radians(g_Input.MouseOffset().y * m_MouseSensitivity);
    m_YRotation += glm::radians(g_Input.MouseOffset().x * m_MouseSensitivity);
    
    // Prevent object flip by keeping m_XRotation beetwen <-60, 60> degrees
    if (m_XRotation > DEGREES_60) {
        m_XRotation = DEGREES_60;
    } else if (m_XRotation < -DEGREES_60) {
        m_XRotation = -DEGREES_60;
    }
    
    // Get whole rotation around Y axis
    glm::quat rot_y(glm::vec3(0.0f, m_YRotation, 0.0f));
    
    // Create new arbitrary X axis
    glm::vec3 curr_rotation_axis = rot_y * m_RotationAxis;
    
    // Calculate new pos by first rotating point around origin and then move it in respect to m_Target
    glm::vec3 new_pos = rot_y * glm::vec3(0.0f, 0.0f, m_Radius);
    new_pos = glm::rotate(new_pos, m_XRotation, curr_rotation_axis);
    new_pos = new_pos + m_Target->Position();
    
    // Calculate rotation between needed to rotate object into m_Target
    // To prevent rotation around the local Z axis calculation were divided into horizontal and vertical
    glm::vec3 diff = m_Target->Position() - new_pos;
    glm::quat front_rot_hor = m_RotationBeetwen(glm::vec3(m_Front.x, 0.0f, m_Front.z), glm::vec3(diff.x, 0.0f, diff.z));
    glm::quat front_rot_ver = m_RotationBeetwen(front_rot_hor * m_Front, diff);
    
    // Apply
    Object().Transform().Position(new_pos);
    Object().Transform().Rotation(front_rot_ver * front_rot_hor);
}

glm::quat ThirdPersonController::m_RotationBeetwen(const glm::vec3 &start, const glm::vec3 &dest) {
    if ((start.x == 0 && start.y == 0 && start.z == 0)
        || (dest.x == 0 && dest.y == 0 && dest.z == 0)) {
        return glm::quat();
    }
    
    glm::vec3 n_start = glm::normalize(start);
    glm::vec3 n_dest = glm::normalize(dest);
    
    float cos_theta = glm::dot(n_start, n_dest);
    glm::vec3 rotation_axis;
    
    if (cos_theta < (-1 + 0.001f)) {
        rotation_axis = cross(glm::vec3(1.0f, 0.0f, 0.0f), n_start);
        if (length2(rotation_axis) < 0.01) {
            rotation_axis = cross(glm::vec3(0.0f, 0.0f, 1.0f), n_start);
        }
        
        rotation_axis = normalize(rotation_axis);
        return glm::angleAxis(glm::radians(180.0f), rotation_axis);
    }
    
    rotation_axis = cross(n_start, n_dest);
    
    float s = sqrt((1.0f + cos_theta) * 2.0f);
    float invs = 1.0f / s;
    
    return glm::quat(s * 0.5f, rotation_axis.x * invs, rotation_axis.y * invs, rotation_axis.z * invs);
}
