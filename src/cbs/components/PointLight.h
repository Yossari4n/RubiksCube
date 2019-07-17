#ifndef PointLight_hpp
#define PointLight_hpp

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "../../rendering/ILightSource.h"
#include "IComponent.h"

class PointLight : public IComponent, public ILightSource {
public:
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
    
    void Initialize() override;
    void Destroy() override;
    
    void SetLightProperties(const ShaderProgram& shader) override;
    
    const glm::vec3& Ambient() const { return m_Ambient; }
    void Ambient(const glm::vec3& ambient);
    
    const glm::vec3& Diffuse() const { return m_Diffuse; }
    void Diffuse(const glm::vec3& diffuse);
    
    const float& Constant() const { return m_Constant; }
    void Constant(float constant);
    
    const float& Linear() const { return m_Linear; }
    void Linear(float linear);
    
    const float& Quadratic() const { return m_Quadratic; }
    void Quadratic(float quadratic);
    
private:
    static int QUANTITY;
    
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
    
    int m_Index;
    float m_Constant;
    float m_Linear;
    float m_Quadratic;
    
    // Keep number in range of <0.0f, 1.0f>
    void NumberInRange(float& number) {
        number = number < 0.0f ? 0.0f : number > 1.0f ? 1.0f : number;
    }
};

#endif
