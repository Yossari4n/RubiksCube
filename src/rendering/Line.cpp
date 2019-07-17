#include "Line.h"

Line::Line(glm::vec3 start, glm::vec3 end, glm::vec3 color)
    : IDrawable(ShaderProgram::Type::PURE_COLOR)
    , m_Start(start)
    , m_End(end)
    , m_Color(color) {
    SetupLine();
}

Line::Line(const Line& other)
    : IDrawable(ShaderProgram::Type::PURE_COLOR)
    , m_Start(other.m_Start)
    , m_End(other.m_End)
    , m_Color(other.m_Color) {
    SetupLine();
}

Line& Line::operator=(const Line &other) {
    if (this == &other) {
        return *this;
    }
    
    m_Start = other.m_Start;
    m_End = other.m_End;
    m_Color = other.m_Color;
    m_ShaderType = ShaderProgram::Type::PURE_COLOR;
    SetupLine();
    
    return *this;
}

Line::~Line() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Line::Draw(const ShaderProgram &shader) const {
    glm::mat4 model(1.0f);
    shader.Uniform("model", model);
    shader.Uniform("color", m_Color);
    
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}

void Line::SetupLine() {
    float vertices[] = { m_Start.x, m_Start.y, m_Start.z, m_End.x, m_End.y, m_End.z };
    
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
