#include "Transform.h"

Transform::Transform()
    : m_Position(glm::vec3(0.0f))
    , m_Rotation(glm::vec3(0.0f))
    , m_Scale(glm::vec3(1.0f)) {
    UpdateModel();
}

const glm::mat4& Transform::Model() {
    return m_Model;
}

void Transform::Position(const glm::vec3& position) {
    m_Position = position;
    
    UpdateModel();
}

void Transform::Move(const glm::vec3& vector) {
    m_Position = m_Position + vector;
    
    UpdateModel();
}

void Transform::MoveRelative(const glm::vec3& vector) {
    m_Position = m_Position + m_Rotation * vector;
}

void Transform::Rotation(const glm::quat &rotation) {
    m_Rotation = rotation;
    
    UpdateModel();
}

void Transform::Rotate(const glm::quat& rotation) {
    m_Rotation =  rotation * m_Rotation;
    
    UpdateModel();
}

void Transform::RotateRelative(const glm::quat& rotation) {
    m_Rotation = m_Rotation * rotation;

    UpdateModel();
}

void Transform::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void Transform::UpdateModel() {
    glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 rotation_matrix = glm::toMat4(m_Rotation);
    glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), m_Scale);
    
    m_Model = translate_matrix * rotation_matrix * scale_matrix;
}
