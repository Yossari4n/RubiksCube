#include "Transform.h"

#include "../Object.h"

Transform::Transform()
    : TransformOut(this, *this)
    , TransformIn(this)
    , PositionOut(this, glm::vec3(0.0f))
    , RotationOut(this, glm::vec3(0.0f))
    , ScaleOut(this, glm::vec3(1.0f))
    , ModelOut(this, glm::mat4(1.0f)) {
    UpdateModel();
}

Transform::Transform(const Transform& other)
    : TransformOut(this, *this)
    , TransformIn(this)
    , PositionOut(this, other.PositionOut)
    , RotationOut(this, other.RotationOut)
    , ScaleOut(this, other.ScaleOut)
    , ModelOut(this, other.ModelOut) {
    UpdateModel();
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
    glm::mat4 model(1.0f);

    if (TransformIn.Connected()) {
        model = TransformIn.Value().Model();
    }

    model = glm::translate(model, PositionOut.Value());
    model = model * glm::toMat4(RotationOut.Value());
    model = glm::scale(model, ScaleOut.Value());

    ModelOut = model;
}
