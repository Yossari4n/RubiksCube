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

    using Face_t = size_t[8][3];

    class Task {
    public:
        Task(RubiksCube& owner, const Face_t& face, float angle, const glm::vec3& axis);

        bool Finished() const { return abs(m_Progress) > abs(m_TargetAngle); }
        void RotateOverTime(float delta);

    private:
        RubiksCube& m_Owner;

        const Face_t& m_Face;
        glm::vec3 m_Axis;
        float m_TargetAngle;
        float m_Current;
        float m_Progress;
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
    void RotateMeshes(const Face_t& face, float angle, glm::vec3 axis);
    void RotateData(const Face_t& face, ERotation rotation);

    Cube_t m_Cube;
    std::queue<Task> m_Tasks;

    static Face_t s_Front, s_Back, s_Left, s_Right, s_Up, s_Down;
};

#endif
