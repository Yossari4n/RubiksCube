#pragma once

#include "IComponent.h"
#include "../../utilities/Time.h"
#include "../../utilities/Input.h"
#include "../../rendering/Cubemap.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>

class Camera : public IComponent {
public:
    Camera(glm::mat4 perspective);
    Camera(float fovy, float aspect, float near, float far);
    Camera(float left, float right, float bottom, float top, float near, float far);
    
    void Initialize() override;
    
    glm::mat4 ViewMatrix() const;
    const glm::mat4& Projection() const { return m_Projection; }
    
private:
    glm::mat4 Perspective(float fovy, float aspect, float near, float far);
    glm::mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);

    glm::mat4 m_ViewMatrix;
    glm::mat4 m_Projection;
    
    Transform* m_Transform;
};
