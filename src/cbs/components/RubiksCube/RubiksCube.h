#ifndef RubiksCube_h
#define RubiksCube_h

#include "Cubie.h"

#include "../Component.h"
#include "../../Object.h"
#include "../../../scenes/Scene.h"
#include "../../message_system/MessageOut.h"

#include "../../../utilities/Input.h"
#include "../../../utilities/Time.h"

#include <string>
#include <vector>
#include <array>
#include <deque>
#include <random>

class RubiksCube : public Component {
    friend class FaceRotation;
    friend class CubeRotation;

    using Row_t    = std::vector<Cubie*>;
    using Matrix_t = std::vector<Row_t>;
    using Cube_t   = std::vector<Matrix_t>;

    struct Face {
        size_t CubiesAround[8][3];
        size_t Center[3];
        glm::vec3 Axis;
        const std::string Siganture;
    };

    class ITask {
    public:
        ITask() = default;
        ITask(const ITask&) = delete;
        ITask& operator=(const ITask&) = delete;
        ITask(ITask&&) = delete;
        ITask& operator=(ITask&&) = delete;

        virtual bool Finished() const = 0;
        virtual std::string Signature() const = 0;
        virtual void Progress(float delta) = 0;
    };

public:
    enum class ERotation {
        CLOCKWISE = -1,
        COUNTER_CLOCKWISE = 1
    };

    enum class EFace {
        FRONT,
        BACK,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    enum class EDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    RubiksCube();

    void Initialize() override;
    void Update() override;
    void Destroy() override;

    void Randomize(unsigned int moves);
    void RotateFace(EFace face, ERotation rotation);
    void RotateCube(EDirection direction);

    MessageOut<std::string> TasksSignaturesOut { this };

private:
    Cube_t m_Cube;
    std::deque<std::unique_ptr<ITask>> m_Tasks;

    Face m_Front, m_Back, m_Left, m_Right, m_Up, m_Down;
};

#endif
