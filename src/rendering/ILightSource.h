#ifndef ILighSource_h
#define ILighSource_h

#include "ShaderProgram.h"

class ILightSource {
public:
    ILightSource() = default;
    virtual ~ILightSource() = default;
    ILightSource(const ILightSource&) = delete;
    ILightSource& operator=(const ILightSource&) = delete;
    ILightSource(ILightSource&&) = delete;
    ILightSource& operator=(ILightSource&&) = delete;

    virtual void SetLightProperties(const ShaderProgram& shader) = 0;
};

#endif
