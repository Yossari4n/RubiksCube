#ifndef ShaderProgram_h
#define ShaderProgram_h

#pragma warning(push, 0)
#include <glad/glad.h>
#include <glm/glm.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class ShaderProgram {
public:
    enum Type : int {
        PURE_COLOR = 0,
        PURE_TEXTURE,
        PHONG,
        SKYBOX,
        
        COUNT
    };
    
    enum Trait : unsigned char {
        NONE = 0,
        LIGHT_RECEIVER = 1 << 0
    };
    
    ShaderProgram();
    // Delete copy semanatics to prevent silent deletion of shader program
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ~ShaderProgram();
    
    void AttachShaders(const char *vertex_path, const char *fragment_path, const char *geometry_path = nullptr);
    void Use() const;
    int ID() const;
    
    Trait Traits() const { return m_Traits; }
    void Traits(Trait traits) { m_Traits = traits; }
    
    // Setters for OpenGL shaders
    void Uniform(const std::string &name, bool value) const;
    void Uniform(const std::string &name, int value) const;
    void Uniform(const std::string &name, float value) const;
    void Uniform(const std::string &name, const glm::vec2 &vec) const;
    void Uniform(const std::string &name, float x, float y) const;
    void Uniform(const std::string &name, const glm::vec3 &vec) const;
    void Uniform(const std::string &name, float x, float y, float z) const;
    void Uniform(const std::string &name, const glm::vec4 &vec) const;
    void Uniform(const std::string &name, float x, float y, float z, float w) const;
    void Uniform(const std::string &name, const glm::mat2 &mat) const;
    void Uniform(const std::string &name, const glm::mat3 &mat) const;
    void Uniform(const std::string &name, const glm::mat4 &mat) const;
    
private:
    void LinkProgram();
    unsigned int AttachShader(const char *path, GLenum shader);
    
    unsigned int m_ID;
    Trait m_Traits;
};

ShaderProgram::Trait operator | (ShaderProgram::Trait lhs, ShaderProgram::Trait rhs);

#endif
