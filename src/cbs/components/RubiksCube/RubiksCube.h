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

    using Row_t    = std::vector<Cubie*>;
    using Matrix_t = std::vector<Row_t>;
    using Cube_t   = std::vector<Matrix_t>;

    struct Face {
        const size_t CubiesAround[8][3];
        const size_t Center[3];
        const glm::vec3 Axis;
        const char Siganture;
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
        CLOCKWISE,
        COUNTER_CLOCKWISE
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
    void RotateMeshes(const Face& face, float angle);
    void RotateData(const Face& face, ERotation rotation);
    
    Cube_t m_Cube;
    std::deque<std::unique_ptr<ITask>> m_Tasks;

    static Face s_Front, s_Back, s_Left, s_Right, s_Up, s_Down;
};

#endif
