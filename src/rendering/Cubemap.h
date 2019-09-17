#ifndef Cubemap_h
#define Cubemap_h

#include "../rendering/Drawable.h"

#pragma warning(push, 0)
#include <stb/stb_image.h>
#pragma warning(pop)

#include <iostream>
#include <string>

class Cubemap : public Drawable {
public:
    Cubemap(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front, ShaderProgram::Type type);
    
    void Draw(const ShaderProgram& shader) const override;
    
private:
    unsigned int m_ID;
    unsigned int m_VAO;
    unsigned int m_VBO;
    
    void m_Load(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void m_Initialize();
};

#endif
