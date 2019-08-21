#include "Cubie.h"

Cubie::Cubie(glm::vec3 position, EColor front, EColor left, EColor right, EColor top, EColor bottom)
    : IDrawable(ShaderProgram::Type::PURE_COLOR)
    , m_ID(0)
    , m_FrontFace(front)
    , m_LeftFace(left)
    , m_RightFace(right)
    , m_TopFace(top)
    , m_BottomFace(bottom)
    , m_Position(position)
    , m_Rotation(glm::vec3(0.0f))
    , m_Model(1.0f) {
    SetupCubie(ColorToVec(front), ColorToVec(left), ColorToVec(right), ColorToVec(top), ColorToVec(bottom));
}

Cubie::~Cubie() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VAO);
}

void Cubie::Draw(const ShaderProgram& shader) const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
    model = model * glm::toMat4(m_Rotation);

    shader.Uniform("model", model);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 396);
    glBindVertexArray(0);
}

void Cubie::RotateAround(float angle, glm::vec3 axis) {
    angle = glm::radians(angle);

    m_Position = glm::rotate(m_Position, angle, axis);
    m_Rotation = glm::quat(axis * angle) * m_Rotation;
}

void Cubie::RotationAround(float angle, glm::vec3 axis) {
    angle = glm::radians(angle);

    m_Position = glm::rotate(m_Position, angle, axis);
    m_Rotation = glm::quat(axis * angle);
}

Cubie::EColor Cubie::XColor(int direction) {
    return BLACK;
}

Cubie::EColor Cubie::YColor(int direction) {
    return BLACK;
}

Cubie::EColor Cubie::ZColor(int direction) {
    return BLACK;
}

glm::vec3 Cubie::ColorToVec(Cubie::EColor color) const {
    float b = static_cast<float>(color & 0xFF);
    float g = static_cast<float>((color >> 8) & 0xFF);
    float r = static_cast<float>((color >> 16) & 0xFF);
    return glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}

void Cubie::SetupCubie(glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 top, glm::vec3 bottom) {
    float vertices[] = {
        // position           // color
        // Right wall
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        // Right face
        -0.45f, -0.45f, -0.501f,  right.x,  right.y,  right.z,
         0.45f, -0.45f, -0.501f,  right.x,  right.y,  right.z,
         0.45f,  0.45f, -0.501f,  right.x,  right.y,  right.z,
         0.45f,  0.45f, -0.501f,  right.x,  right.y,  right.z,
        -0.45f,  0.45f, -0.501f,  right.x,  right.y,  right.z,
        -0.45f, -0.45f, -0.501f,  right.x,  right.y,  right.z,


        // Left wall
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        // Left face
        -0.45f, -0.45f,  0.501f,  left.x,  left.y,  left.z,
         0.45f, -0.45f,  0.501f,  left.x,  left.y,  left.z,
         0.45f,  0.45f,  0.501f,  left.x,  left.y,  left.z,
         0.45f,  0.45f,  0.501f,  left.x,  left.y,  left.z,
        -0.45f,  0.45f,  0.501f,  left.x,  left.y,  left.z,
        -0.45f, -0.45f,  0.501f,  left.x,  left.y,  left.z,


        // Front wall
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         // Front face
         0.501f,  0.45f,  0.45f, front.x,  front.y,  front.z,
         0.501f,  0.45f, -0.45f, front.x,  front.y,  front.z,
         0.501f, -0.45f, -0.45f, front.x,  front.y,  front.z,
         0.501f, -0.45f, -0.45f, front.x,  front.y,  front.z,
         0.501f, -0.45f,  0.45f, front.x,  front.y,  front.z,
         0.501f,  0.45f,  0.45f, front.x,  front.y,  front.z,


         // Bottom wall
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        // Bottom face
        -0.45f, -0.501f, -0.45f,  bottom.x,  bottom.y,  bottom.z,
         0.45f, -0.501f, -0.45f,  bottom.x,  bottom.y,  bottom.z,
         0.45f, -0.501f,  0.45f,  bottom.x,  bottom.y,  bottom.z,
         0.45f, -0.501f,  0.45f,  bottom.x,  bottom.y,  bottom.z,
        -0.45f, -0.501f,  0.45f,  bottom.x,  bottom.y,  bottom.z,
        -0.45f, -0.501f, -0.45f,  bottom.x,  bottom.y,  bottom.z,

        // Top wall
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        // Top face
        -0.45f,  0.501f, -0.45f,  top.x,  top.y,  top.z,
         0.45f,  0.501f, -0.45f,  top.x,  top.y,  top.z,
         0.45f,  0.501f,  0.45f,  top.x,  top.y,  top.z,
         0.45f,  0.501f,  0.45f,  top.x,  top.y,  top.z,
        -0.45f,  0.501f,  0.45f,  top.x,  top.y,  top.z,
        -0.45f,  0.501f, -0.45f,  top.x,  top.y,  top.z,

        // Back wall
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}