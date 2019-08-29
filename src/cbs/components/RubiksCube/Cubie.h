#ifndef Cubie_h
#define Cubie_h

#include "../../../rendering/Drawable.h"

#define GLM_ENABLE_EXPERIMENTAL
#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#pragma warning(pop)

class Cubie : public Drawable {
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

    Cubie(const glm::mat4* parent, glm::vec3 position, EColor front, EColor left = BLACK, EColor right = BLACK, EColor top = BLACK, EColor bottom = BLACK);
    ~Cubie();

    void Draw(const ShaderProgram& shader) const override;

    void RotateAround(float angle, glm::vec3 axis);
    void RotationAround(float angle, glm::vec3 axis);

private:
    glm::vec3 ColorToVec(Cubie::EColor color) const;
    void SetupCubie(glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 top, glm::vec3 bottom);

    // Colors for each face
    EColor m_FrontFace;
    EColor m_LeftFace;
    EColor m_RightFace;
    EColor m_TopFace;
    EColor m_BottomFace;

    const glm::mat4* m_ParentModel;
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::mat4 m_Model;

    GLuint m_VAO;
    GLuint m_VBO;
};

#endif
