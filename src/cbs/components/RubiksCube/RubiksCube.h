#ifndef RubiksCube_h
#define RubiksCube_h

#include "Cubie.h"

#include "../IComponent.h"
#include "../../Object.h"
#include "../../../scenes/IScene.h"
#include "../../message_system/PropertyOut.h"

#include "../../../utilities/Input.h"
#include "../../../utilities/Time.h"

#include <iostream>
#include <vector>
#include <array>
#include <queue>

class RubiksCube : public IComponent {
    using Row_t    = std::vector<Cubie*>;
    using Matrix_t = std::vector<Row_t>;
    using Cube_t   = std::vector<Matrix_t>;

    struct Face {
        const size_t CubiesAround[8][3];
        const size_t Center[3];
        const glm::vec3 Axis;
    };

    class Task {
    public:
        Task(RubiksCube& owner, const Face& face, float angle);

        bool Finished() const { return m_Finished; }
        void RotateOverTime(float delta);

    private:
        RubiksCube& m_Owner;

        const Face& m_Face;
        float m_TargetAngle;
        float m_Progress;
        bool m_Finished;
    };

public:
    enum class ERotation {
        CLOCKWISE,
        COUNTER_CLOCKWISE
    };

    RubiksCube();

    void Initialize() override;
    void Update() override;
    void Destroy() override;

private:
    void RotateMeshes(const Face& face, float angle);
    void RotateData(const Face& face, ERotation rotation);

    Cube_t m_Cube;
    std::queue<Task> m_Tasks;

    static Face s_Front, s_Back, s_Left, s_Right, s_Up, s_Down;
};

#endif
