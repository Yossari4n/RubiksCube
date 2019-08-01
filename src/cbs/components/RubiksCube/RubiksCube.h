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
    RubiksCube();

    void Initialize() override;
    void Update() override;
    void Destroy() override;

    void RotateFront(int direction);
    void RotateBack(int direction);
    void RotateLeft(int direction);
    void RotateRight(int direction);
    void RotateUp(int direction);
    void RotateDown(int direction);

    void Print();
    int gcd(int a, int b);

private:
    void RotateFace(const size_t face[8][3], float angle, glm::vec3 axis);

    Cube_t m_Cube;
};

#endif
