#ifndef RubiksCube_h
#define RubiksCube_h

#include "Cubie.h"

#include "../IComponent.h"
#include "../../Object.h"
#include "../../../scenes/IScene.h"
#include "../../message_system/PropertyOut.h"

#include "../../../utilities/Input.h"

#include <vector>
#include <array>

class RubiksCube : public IComponent {
    using Row_t = std::vector<Cubie*>; // TODO maybe change it
    using Matrix_t = std::vector<Row_t>;
    using Cube_t = std::vector<Matrix_t>;

public:
    enum class EFace {
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum ERotation {
        CLOCKWISE = -1,
        COUNTER_CLOCKWISE = 1
    };

    RubiksCube();

    void Initialize() override;
    void Update() override;
    void Destroy() override;

    void Rotate(EFace face, ERotation rotation);

    void RotateFront(ERotation rotation);
    void RotateBack(ERotation rotation);
    void RotateLeft(ERotation rotation);
    void RotateRight(ERotation rotation);
    void RotateUp(ERotation rotation);
    void RotateDown(ERotation rotation);

    int gcd(int a, int b);

private:
    void RotateFace(const size_t face[8][3], float angle, glm::vec3 axis);
    void Print();

    Cube_t m_Cube;
};

#endif
