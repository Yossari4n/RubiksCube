#include "Transform.h"

#include "../Object.h"

Transform::Transform() {
    RegisterConnection(Parent);
    RegisterConnection(TransformOut);
    RegisterConnection(ModelOut);
    RegisterConnection(PositionOut);
    RegisterConnection(RotationOut);
    RegisterConnection(ScaleOut);
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
