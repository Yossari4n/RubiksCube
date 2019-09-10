#ifndef Mesh_h
#define Mesh_h

#include "../../../rendering/ShaderProgram.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    GLuint ID = 0;
    std::string Type;
    std::string Path;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex> &verticies, const std::vector<unsigned int> &indicies, const std::vector<Texture> &textures);
    Mesh() = delete;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    ~Mesh();

    void Draw(const ShaderProgram &shader) const;

    const std::vector<Vertex>& Vertices() const { return m_Vertices; }

    const std::vector<unsigned int>& Indicies() const { return m_Indices; }

    const std::vector<Texture>& Textures() const { return m_Textures; }

private:
    void SetupMesh();

    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};

#endif
