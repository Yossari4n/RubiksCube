#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : m_Direction(direction)
    , m_Ambient(ambient)
    , m_Diffuse(diffuse)
    , m_Specular(specular) {
}

void DirectionalLight::Initialize() {
    Object().Scene().RegisterLightSource(this);
}

void DirectionalLight::Destroy() {
    Object().Scene().UnregisterLightSource(this);
}

void DirectionalLight::SetLightProperties(const ShaderProgram& shader) {
    shader.Uniform("dirLight.direction", m_Direction);
    shader.Uniform("dirLight.ambient", m_Ambient);
    shader.Uniform("dirLight.diffuse", m_Diffuse);
    shader.Uniform("dirLight.specular", m_Specular);
}
