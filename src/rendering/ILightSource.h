#ifndef ILighSource_h
#define ILighSource_h

#include "ShaderProgram.h"

class ILightSource {
public:
    virtual void SetLightProperties(const ShaderProgram& shader) = 0;
};

#endif
