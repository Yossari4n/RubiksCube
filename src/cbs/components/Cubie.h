#ifndef Cubie_h
#define Cubie_h

#include "IComponent.h"
#include "../Object.h"
#include "../message_system/PropertyIn.h"
#include "../../scenes/IScene.h"
#include "../../rendering/IDrawable.h"


#include <array>

constexpr glm::vec3 BLACK(0.0f);
constexpr glm::vec3 WHITE(1.0f);
constexpr glm::vec3 YELLOW(1.0f, 1.0f, 0.0f);
constexpr glm::vec3 GREEN(0.0f, 1.0f, 0.0f);
constexpr glm::vec3 RED(1.0f, 0.0f, 0.0f);
constexpr glm::vec3 BLUE(0.0f, 0.0f, 1.0f);
constexpr glm::vec3 ORANGE(1.0f, 0.65f, 0.0f);

class Cubie : public IComponent, public IDrawable {
public:
    Cubie(glm::vec3 front, glm::vec3 left = BLACK, glm::vec3 right = BLACK, glm::vec3 top = BLACK, glm::vec3 bottom = BLACK);
    ~Cubie();

    void Initialize() override;
    void Destroy() override;

    void Draw(const ShaderProgram& shader) const override;

    PropertyIn<glm::mat4> Model{ this };

private:
    void SetupCubie();

    glm::vec3 m_FrontFace;
    glm::vec3 m_LeftFace;
    glm::vec3 m_RightFace;
    glm::vec3 m_TopFace;
    glm::vec3 m_BottomFace;

    unsigned int m_VAO;
    unsigned int m_VBO;
};

#endif
