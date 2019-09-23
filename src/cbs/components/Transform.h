#ifndef Transform_h
#define Transform_h

#include "Component.h"
#include "../message_system/PropertyOut.h"
#include "../message_system/PropertyIn.h"

#define GLM_ENABLE_EXPERIMENTAL
#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#pragma warning(pop)

class Transform : public Component {
public:

    void MakeConnectors(MessageManager& message_manager) override;
    void Initialize() override;

    const glm::mat4& Model() const;
    
    const glm::vec3& Position() const;
    void Position(const glm::vec3& position);
    void Move(const glm::vec3& vector);
    void MoveRelative(const glm::vec3& vector);

    const glm::quat& Rotation() const;
    void Rotation(const glm::quat& rotation);
    void Rotate(const glm::quat& rotation);
    void RotateRelative(const glm::quat& rotation);

    const glm::vec3& Scale() const;
    void Scale(const glm::vec3& scale);

    glm::vec3 Front() { return RotationOut.Value() * glm::vec3(1.0f, 0.0f, 0.0f); }
    glm::vec3 Up() { return RotationOut.Value() * glm::vec3(0.0f, 1.0f, 0.0f); }
    glm::vec3 Right() { return RotationOut.Value() * glm::vec3(0.0f, 0.0f, 1.0f); }

    PropertyIn<Transform> Parent;

    PropertyOut<Transform*> TransformOut;

    PropertyOut<glm::mat4> ModelOut;
    PropertyOut<glm::vec3> PositionOut;
    PropertyOut<glm::quat> RotationOut;
    PropertyOut<glm::vec3> ScaleOut;

private:
    void UpdateModel();
};

#endif
