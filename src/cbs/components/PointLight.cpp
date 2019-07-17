#include "PointLight.h"

int PointLight::QUANTITY = 0;

PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
    : m_Ambient(ambient)
    , m_Diffuse(diffuse)
    , m_Specular(specular)
    , m_Constant(constant)
    , m_Linear(linear)
    , m_Quadratic(quadratic) {
    // Make sure parameters are not negative
    m_Constant = m_Constant <= 0 ? 0.0000001f : m_Constant;
    m_Linear = m_Linear <= 0 ? 0.0000001f : m_Linear;
    m_Quadratic = m_Quadratic <= 0 ? 0.0000001f : m_Quadratic;
    m_Index = QUANTITY;
    
    QUANTITY = (QUANTITY + 1) % 4;
}

void PointLight::Initialize() {
    Object().Scene().RegisterLightSource(this);
}

void PointLight::Destroy() {
    Object().Scene().UnregisterLightSource(this);
}

void PointLight::SetLightProperties(const ShaderProgram& shader) {
    std::string pointLight = "pointLights[" + std::to_string(m_Index) + "].";
    
    shader.Uniform(pointLight + "position", Object().Transform().Position());
    shader.Uniform(pointLight + "ambient", m_Ambient);
    shader.Uniform(pointLight + "diffuse", m_Diffuse);
    shader.Uniform(pointLight + "constant", m_Constant);
    shader.Uniform(pointLight + "linear", m_Linear);
    shader.Uniform(pointLight + "quadratic", m_Quadratic);
}

void PointLight::Ambient(const glm::vec3& ambient) {
    m_Ambient = ambient;
    
    NumberInRange(m_Ambient.x);
    NumberInRange(m_Ambient.y);
    NumberInRange(m_Ambient.z);
}

void PointLight::Diffuse(const glm::vec3& diffuse) {
    m_Diffuse = diffuse;
    
    NumberInRange(m_Diffuse.x);
    NumberInRange(m_Diffuse.y);
    NumberInRange(m_Diffuse.z);
}

void PointLight::Constant(float constant) {
    if (constant <= 0) {
        constant = 0.0000001f;
    }
    
    m_Constant = constant;
}

void PointLight::Linear(float linear) {
    if (linear <= 0) {
        linear = 0.0000001f;
    }
    
    m_Linear = linear;
}

void PointLight::Quadratic(float quadratic) {
    if (quadratic <= 0) {
        quadratic = 0.0000001f;
    }
    
    m_Quadratic = quadratic;
}
