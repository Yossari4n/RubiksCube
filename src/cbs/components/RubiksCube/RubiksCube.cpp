#include "RubiksCube.h"
#include "Tasks.h"


RubiksCube::RubiksCube(class Object& owner)
    : Component(owner)
    , m_Front {
        {
            { 0, 0, 0 },
            { 0, 0, 1 },
            { 0, 0, 2 },
            { 0, 1, 2 },
            { 0, 2, 2 },
            { 0, 2, 1 },
            { 0, 2, 0 },
            { 0, 1, 0 }
        },
        { 0, 1, 1 },
        { glm::vec3(1.0f, 0.0f, 0.0f) },
        { 'F' } }
    , m_Back {
        {
            { 2, 0, 2 },
            { 2, 0, 1 },
            { 2, 0, 0 },
            { 2, 1, 0 },
            { 2, 2, 0 },
            { 2, 2, 1 },
            { 2, 2, 2 },
            { 2, 1, 2 }
        },
        { 2, 1, 1 },
        { glm::vec3(-1.0f, 0.0f, 0.0f) },
        { 'B' } }
    , m_Left {
        {
            {2, 0, 0},
            {1, 0, 0},
            {0, 0, 0},
            {0, 1, 0},
            {0, 2, 0},
            {1, 2, 0},
            {2, 2, 0},
            {2, 1, 0}
        },
        { 1, 1, 0 },
        { glm::vec3(0.0f, 0.0f, 1.0f) },
        { 'L' } }
    , m_Right {
        {
            {0, 0, 2},
            {1, 0, 2},
            {2, 0, 2},
            {2, 1, 2},
            {2, 2, 2},
            {1, 2, 2},
            {0, 2, 2},
            {0, 1, 2}
        },
        { 1, 1, 2 },
        { glm::vec3(0.0f, 0.0f, -1.0f) },
        { 'R' } }
    , m_Up {
        {
            {2, 0, 0},
            {2, 0, 1},
            {2, 0, 2},
            {1, 0, 2},
            {0, 0, 2},
            {0, 0, 1},
            {0, 0, 0},
            {1, 0, 0}
        },
        { 1, 0, 1 },
        { glm::vec3(0.0f, 1.0f, 0.0f) },
        { 'U' } }
    , m_Down {
        {
            {1, 2, 2},
            {2, 2, 2},
            {2, 2, 1},
            {2, 2, 0},
            {1, 2, 0},
            {0, 2, 0},
            {0, 2, 1},
            {0, 2, 2}
        },
        { 1, 2, 1 },
        { glm::vec3(0.0f, -1.0f, 0.0f) },
        { 'D' } } {

    for (int matrix = 0; matrix < 3; matrix++) {
        m_Cube.emplace_back();
        for (int row = 0; row < 3; row++) {
            m_Cube[matrix].emplace_back();
            m_Cube[matrix][row].reserve(3);
        }
    }
}

void RubiksCube::Initialize() {
    const glm::mat4* root_model = &Object().Root().ModelOut.Value();

    // Front face
    // First row
    m_Cube[0][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 1.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::WHITE));
    m_Cube[0][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE));
    m_Cube[0][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 1.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE, Cubie::EColor::WHITE));
    // Second row
    m_Cube[0][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED));
    m_Cube[0][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::BLUE));
    m_Cube[0][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE));
    // Third row
    m_Cube[0][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, -1.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[0][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[0][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, -1.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));

    // Back face
    // First row
    m_Cube[2][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 1.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED, Cubie::EColor::WHITE));
    m_Cube[2][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE));
    m_Cube[2][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 1.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::WHITE));

    // Second row
    m_Cube[2][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED));
    m_Cube[2][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::GREEN));
    m_Cube[2][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE));

    // Third row
    m_Cube[2][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, -1.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[2][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[2][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, -1.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    for (auto row = m_Cube[2].begin(); row != m_Cube[2].end(); row++) {
        for (auto cubie = row->begin(); cubie != row->end(); cubie++) {
            (*cubie)->RotateAround(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }

    // Middle face
    // First row
    m_Cube[1][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::WHITE, Cubie::EColor::RED))->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));;
    m_Cube[1][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::WHITE))->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));;
    m_Cube[1][0].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::WHITE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE))->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));;

    // Second row
    m_Cube[1][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::RED))->RotateAround(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_Cube[1][1].emplace_back(new Cubie(root_model, glm::vec3(0.0f, 0.0f, 0.0f), Cubie::EColor::BLACK)); // Hidden cubie in the center
    m_Cube[1][1].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::ORANGE))->RotateAround(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Third row
    m_Cube[1][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::YELLOW, Cubie::EColor::RED))->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    m_Cube[1][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::YELLOW))->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    m_Cube[1][2].emplace_back(new Cubie(root_model, glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::YELLOW, Cubie::EColor::BLACK, Cubie::EColor::ORANGE))->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));


    // Register draw calls for all cubies
    for (auto matrix = m_Cube.begin(); matrix != m_Cube.end(); matrix++) {
        for (auto row = matrix->begin(); row != matrix->end(); row++) {
            for (auto cube = row->begin(); cube != row->end(); cube++) {
                Object().Scene().RegisterDrawCall(*cube);
            }
        }
    }

    RegisterUpdateCall();
}

void RubiksCube::Update() {
    // Collect next task 
    if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_F)) {
        RotateFace(EFace::FRONT, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_F) == Input::EKeyState::PRESSED) {
        RotateFace(EFace::FRONT, ERotation::CLOCKWISE);
    } else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_B)) {
        RotateFace(EFace::BACK, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_B) == Input::EKeyState::PRESSED) {
        RotateFace(EFace::BACK, ERotation::CLOCKWISE);
    } else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_L)) {
        RotateFace(EFace::LEFT, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_L) == Input::EKeyState::PRESSED) {
        RotateFace(EFace::LEFT, ERotation::CLOCKWISE);
    } else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_R)) {
        RotateFace(EFace::RIGHT, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_R) == Input::EKeyState::PRESSED) {
        RotateFace(EFace::RIGHT, ERotation::CLOCKWISE);
    } else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_U)) {
        RotateFace(EFace::UP, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_U) == Input::EKeyState::PRESSED) {
        RotateFace(EFace::UP, ERotation::CLOCKWISE);
    } else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_D)) {
        RotateFace(EFace::DOWN, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_D) == Input::EKeyState::PRESSED) {
        RotateFace(EFace::DOWN, ERotation::CLOCKWISE);
    } else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_X)) {
        RotateCube(EDirection::RIGHT, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_X) == Input::EKeyState::PRESSED) {
        RotateCube(EDirection::RIGHT, ERotation::CLOCKWISE);
    } else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_Y)) {
        RotateCube(EDirection::UP, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_Y) == Input::EKeyState::PRESSED) {
        RotateCube(EDirection::UP, ERotation::CLOCKWISE);
    }  else if (g_Input.KeyHold(GLFW_KEY_LEFT_SHIFT) && g_Input.KeyPressed(GLFW_KEY_Z)) {
        RotateCube(EDirection::FRONT, ERotation::COUNTER_CLOCKWISE);
    } else if (g_Input.KeyState(GLFW_KEY_Z) == Input::EKeyState::PRESSED) {
        RotateCube(EDirection::FRONT, ERotation::CLOCKWISE);
    }

    // Update deque of tasks
    if (!m_Tasks.empty()) {
        if (!m_Tasks.front()->Finished()) {
            m_Tasks.front()->Progress(g_Time.FixedDeltaTime());
        } else {
            m_Tasks.pop_front();
            UpdateTextRenderer();
        }
    }
}

void RubiksCube::Destroy() {
    for (auto matrix = m_Cube.begin(); matrix != m_Cube.end(); matrix++) {
        for (auto row = matrix->begin(); row != matrix->end(); row++) {
            for (auto cube = row->begin(); cube != row->end(); cube++) {
                Object().Scene().UnregisterDrawCall(*cube);
                delete *cube;
            }
        }
    }
}

void RubiksCube::RotateFace(EFace face, ERotation rotation) {
    Face& face_to_rotate = [&]() -> Face& {
        switch (face) {
        case EFace::FRONT:
            return m_Front;

        case EFace::BACK:
            return m_Back;

        case EFace::UP:
            return m_Up;

        case EFace::DOWN:
            return m_Down;

        case EFace::LEFT:
            return m_Left;

        default: // case EFace::RIGHT
            return m_Right;
        };
    }();

    m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, face_to_rotate, rotation, 90.0f, FACE_ROTATION_SPEED));
    UpdateTextRenderer();
}

void RubiksCube::RotateCube(EDirection direction, ERotation rotation) {
    m_Tasks.emplace_back(std::make_unique<CubeRotation>(*this, &Object().Root(), direction, rotation, CUBE_ROTATION_SPEED));
    UpdateTextRenderer();
}

void RubiksCube::Randomize(unsigned int moves) {
    if (m_Tasks.size() > 0) {
        // Finish current task
        m_Tasks.front()->Progress(1.0f);
        m_Tasks.clear();
    }

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 5);
    for (unsigned int i = 0; i < moves; i++) {
        // 50% chances for clockwise and 50% chances for counter-clockwise rotation
        auto rn = distribution(generator);
        ERotation rotation = rn % 2 == 0 ? ERotation::CLOCKWISE : ERotation::COUNTER_CLOCKWISE;

        // Each face has equal chance to be choosen
        rn = distribution(generator);
        switch (rn) {
        case 0:
            RotateFace(EFace::FRONT, rotation);
            break;

        case 1:
            RotateFace(EFace::BACK, rotation);
            break;

        case 2:
            RotateFace(EFace::UP, rotation);
            break;

        case 3:
            RotateFace(EFace::DOWN, rotation);
            break;

        case 4:
            RotateFace(EFace::LEFT, rotation);
            break;

        case 5:
            RotateFace(EFace::RIGHT, rotation);
            break;
        }
    }
}

void RubiksCube::UpdateTextRenderer() {
    std::string message;
    message.reserve(m_Tasks.size() * 2);
    for (auto it = m_Tasks.begin(); it != m_Tasks.end(); it++) {
        message += ' ' + (*it)->Signature();
    }
    TasksSignaturesOut.Send(message);
}
