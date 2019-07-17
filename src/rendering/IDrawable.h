#ifndef IDrawable_h
#define IDrawable_h

#include "ShaderProgram.h"

class IDrawable {
public:
    IDrawable(ShaderProgram::Type shader_type);

    virtual void Draw(const ShaderProgram &shader) const = 0;
    
    ShaderProgram::Type ShaderType() const { return m_ShaderType; }
    void ShaderType(ShaderProgram::Type type) { m_ShaderType = type; }
    
protected:
    ShaderProgram::Type m_ShaderType;
};

#endif