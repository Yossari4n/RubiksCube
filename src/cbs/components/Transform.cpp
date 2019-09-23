#include "Transform.h"

#include "../Object.h"


void Transform::MakeConnectors(MessageManager& message_manager) {
    message_manager.Make(this, Parent);

    message_manager.Make(this, TransformOut);
    message_manager.Make(this, ModelOut);
    message_manager.Make(this, PositionOut, glm::vec3(0.0f));
    message_manager.Make(this, RotationOut, glm::vec3(0.0f));
    message_manager.Make(this, ScaleOut, glm::vec3(1.0f));
}

void Transform::Initialize() {
    UpdateModel();
}

const glm::mat4& Transform::Model() const {
    return ModelOut.Value();
}

const glm::vec3& Transform::Position() const {
    return PositionOut.Value();
}

void Transform::Position(const glm::vec3& position) {
    PositionOut = position;

    UpdateModel();
}

void Transform::Move(const glm::vec3& vector) {
    PositionOut = PositionOut.Value() + vector;

    UpdateModel();
}

void Transform::MoveRelative(const glm::vec3& vector) {
    PositionOut = PositionOut.Value() + RotationOut.Value() * vector;

    UpdateModel();
}

const glm::quat& Transform::Rotation() const {
    return RotationOut.Value();
}

void Transform::Rotation(const glm::quat &rotation) {
    RotationOut = rotation;

    UpdateModel();
}

void Transform::Rotate(const glm::quat& rotation) {
    RotationOut = rotation * RotationOut.Value();

    UpdateModel();
}

void Transform::RotateRelative(const glm::quat& rotation) {
    RotationOut = RotationOut.Value() * rotation;

    UpdateModel();
}

const glm::vec3& Transform::Scale() const {
    return ScaleOut.Value();
}

void Transform::Scale(const glm::vec3& scale) {
    ScaleOut = scale;
    
    UpdateModel();
}

void Transform::UpdateModel() {
    if (Parent.Connected()) {
        ModelOut = Parent.Value().Model();
    } else {
        ModelOut = glm::mat4(1.0f);
    }

    ModelOut = glm::translate(ModelOut.Value(), PositionOut.Value());
    ModelOut = ModelOut.Value() * glm::toMat4(RotationOut.Value());
    ModelOut = glm::scale(ModelOut.Value(), ScaleOut.Value());
}
