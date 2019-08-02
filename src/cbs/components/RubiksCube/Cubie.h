#ifndef Cubie_h
#define Cubie_h

#include "../../../rendering/IDrawable.h"

#define GLM_ENABLE_EXPERIMENTAL
#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#pragma warning(pop)

class Cubie : public IDrawable {
public:
    enum EColor {
        BLACK = 0x000000,
        WHITE = 0xFFFFFF,
        RED = 0xFF0000,
        GREEN = 0x00FF00,
        BLUE = 0x0000FF,
        YELLOW = 0xFFFF00,
        ORANGE = 0xFF4500
    };

    Cubie(glm::vec3 position, EColor front, EColor left = BLACK, EColor right = BLACK, EColor top = BLACK, EColor bottom = BLACK);
    ~Cubie();

    void Draw(const ShaderProgram& shader) const override;

    void RotateAround(float angle, glm::vec3 axis);
    EColor XColor(int direction);
    EColor YColor(int direction);
    EColor ZColoe(int direction);

    // TODO delete before ship or leave it but fix it to proper form
    int m_ID;

private:
    glm::vec3 ColorToVec(Cubie::EColor color) const;
    void SetupCubie(glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 top, glm::vec3 bottom);

    // Colors for each face
    EColor m_FrontFace;
    EColor m_LeftFace;
    EColor m_RightFace;
    EColor m_TopFace;
    EColor m_BottomFace;

    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::mat4 m_Model;

    unsigned int m_VAO;
    unsigned int m_VBO;
};

#endif
