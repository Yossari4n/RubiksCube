#ifndef Drawable_h
#define Drawable_h

#include "ShaderProgram.h"

class Drawable {
public:
    Drawable(ShaderProgram::Type shader_type);
    virtual ~Drawable() = default;
    Drawable(const Drawable&) = delete;
    Drawable& operator=(const Drawable&) = delete;
    Drawable(Drawable&&) = delete;
    Drawable* operator=(Drawable&&) = delete;

    virtual void Draw(const ShaderProgram &shader) const = 0;

    ShaderProgram::Type ShaderType() const { return m_ShaderType; }
    void ShaderType(ShaderProgram::Type type) { m_ShaderType = type; }

protected:
    ShaderProgram::Type m_ShaderType;
};

#endif