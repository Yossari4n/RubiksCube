#include "Cubie.h"

Cubie::Cubie(glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 top, glm::vec3 bottom)
    : IDrawable(ShaderProgram::Type::PURE_COLOR)
    , m_FrontFace(front)
    , m_LeftFace(left)
    , m_RightFace(right)
    , m_TopFace(top)
    , m_BottomFace(bottom) {
    SetupCubie();
}

Cubie::~Cubie() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VAO);
}

void Cubie::Draw(const ShaderProgram& shader) const {
    shader.Uniform("model", Model);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 396);
    glBindVertexArray(0);
}

void Cubie::SetupCubie() {
    float verticies[] = {
        // position           // color
        // Right wall
        -0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        // Right face
        -0.45f, -0.45f, -0.491f,  m_RightFace.x, m_RightFace.y, m_RightFace.z,
         0.45f, -0.45f, -0.491f,  m_RightFace.x, m_RightFace.y, m_RightFace.z,
         0.45f,  0.45f, -0.491f,  m_RightFace.x, m_RightFace.y, m_RightFace.z,
         0.45f,  0.45f, -0.491f,  m_RightFace.x, m_RightFace.y, m_RightFace.z,
        -0.45f,  0.45f, -0.491f,  m_RightFace.x, m_RightFace.y, m_RightFace.z,
        -0.45f, -0.45f, -0.491f,  m_RightFace.x, m_RightFace.y, m_RightFace.z,


        // Left wall
        -0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        // Left face
        -0.45f, -0.45f,  0.491f,  m_LeftFace.x, m_LeftFace.y, m_LeftFace.z,
         0.45f, -0.45f,  0.491f,  m_LeftFace.x, m_LeftFace.y, m_LeftFace.z,
         0.45f,  0.45f,  0.491f,  m_LeftFace.x, m_LeftFace.y, m_LeftFace.z,
         0.45f,  0.45f,  0.491f,  m_LeftFace.x, m_LeftFace.y, m_LeftFace.z,
        -0.45f,  0.45f,  0.491f,  m_LeftFace.x, m_LeftFace.y, m_LeftFace.z,
        -0.45f, -0.45f,  0.491f,  m_LeftFace.x, m_LeftFace.y, m_LeftFace.z,


        // Front wall
         0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         // Front face
         0.491f,  0.45f,  0.45f,  m_FrontFace.x, m_FrontFace.y, m_FrontFace.z,
         0.491f,  0.45f, -0.45f,  m_FrontFace.x, m_FrontFace.y, m_FrontFace.z,
         0.491f, -0.45f, -0.45f,  m_FrontFace.x, m_FrontFace.y, m_FrontFace.z,
         0.491f, -0.45f, -0.45f,  m_FrontFace.x, m_FrontFace.y, m_FrontFace.z,
         0.491f, -0.45f,  0.45f,  m_FrontFace.x, m_FrontFace.y, m_FrontFace.z,
         0.491f,  0.45f,  0.45f,  m_FrontFace.x, m_FrontFace.y, m_FrontFace.z,


         // Bottom wall
        -0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        // Bottom face
        -0.45f, -0.491f, -0.45f,  m_BottomFace.x, m_BottomFace.y, m_BottomFace.z,
         0.45f, -0.491f, -0.45f,  m_BottomFace.x, m_BottomFace.y, m_BottomFace.z,
         0.45f, -0.491f,  0.45f,  m_BottomFace.x, m_BottomFace.y, m_BottomFace.z,
         0.45f, -0.491f,  0.45f,  m_BottomFace.x, m_BottomFace.y, m_BottomFace.z,
        -0.45f, -0.491f,  0.45f,  m_BottomFace.x, m_BottomFace.y, m_BottomFace.z,
        -0.45f, -0.491f, -0.45f,  m_BottomFace.x, m_BottomFace.y, m_BottomFace.z,

        // Top wall
        -0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
         0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        // Top face
        -0.45f,  0.491f, -0.45f, m_TopFace.x, m_TopFace.y, m_TopFace.z,
         0.45f,  0.491f, -0.45f, m_TopFace.x, m_TopFace.y, m_TopFace.z,
         0.45f,  0.491f,  0.45f, m_TopFace.x, m_TopFace.y, m_TopFace.z,
         0.45f,  0.491f,  0.45f, m_TopFace.x, m_TopFace.y, m_TopFace.z,
        -0.45f,  0.491f,  0.45f, m_TopFace.x, m_TopFace.y, m_TopFace.z,
        -0.45f,  0.491f, -0.45f, m_TopFace.x, m_TopFace.y, m_TopFace.z,

        // Back wall
        -0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f,  0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f, -0.49f, -0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f, -0.49f,  0.49f,  0.0f, 0.0f, 0.0f,
        -0.49f,  0.49f,  0.49f,  0.0f, 0.0f, 0.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}