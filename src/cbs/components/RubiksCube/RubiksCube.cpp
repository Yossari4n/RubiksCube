#include "RubiksCube.h"
#include "Tasks.h"


RubiksCube::RubiksCube() 
    : m_Front {
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
    const float FACE_ROTATION_SPEED = 2.0f;
    const float CUBE_ROTATION_SPEED = 2.0f;
    const unsigned int RANDOM_MOVES = 30;

    // Collect next task 
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_F) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Front, ERotation::COUNTER_CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_F) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Front, ERotation::CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Back, ERotation::COUNTER_CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Back, ERotation::CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_L) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Left, ERotation::COUNTER_CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_L) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Left, ERotation::CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_R) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Right, ERotation::COUNTER_CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_R) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Right, ERotation::CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_U) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Up, ERotation::COUNTER_CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_U) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Up, ERotation::CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Down, ERotation::COUNTER_CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Down, ERotation::CLOCKWISE, 90.0f, FACE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_UP) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<CubeRotation>(*this, &Object().Root(), EDirection::UP, CUBE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_DOWN) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<CubeRotation>(*this, &Object().Root(), EDirection::DOWN, CUBE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<CubeRotation>(*this, &Object().Root(), EDirection::LEFT, CUBE_ROTATION_SPEED));
    } else if (g_Input.GetKeyState(GLFW_KEY_RIGHT) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(std::make_unique<CubeRotation>(*this, &Object().Root(), EDirection::RIGHT, CUBE_ROTATION_SPEED));
    }

    // Update deque of tasks
    if (!m_Tasks.empty()) {
        if (!m_Tasks.front()->Finished()) {
            m_Tasks.front()->Progress(g_Time.FixedDeltaTime());
        } else {
            m_Tasks.pop_front();
        }

        std::string message;
        message.reserve(m_Tasks.size() * 2);
        for (auto it = m_Tasks.begin(); it != m_Tasks.end(); it++) {
            message += ' ' + (*it)->Signature();
        }
        TasksSignaturesOut.Send(message);
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

void RubiksCube::Randomize(unsigned int moves) {
    const float ROTATION_SPEED = 3.0f;
    const float ANGLE = 90.0f;

    if (m_Tasks.size() > 0) {
        // Finish current task
        m_Tasks.front()->Progress(1.0f);
        
        m_Tasks.clear();
    }

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 5);
    for (unsigned int i = 0; i < moves; i++) {
        int rn = distribution(generator);

        // 50% chances for clockwise and 50% chances for counter-clockwise rotation
        ERotation rotation = rn % 2 == 0 ? ERotation::CLOCKWISE : ERotation::COUNTER_CLOCKWISE;

        // Each face has equal chance to be choosen
        switch (rn) {
        case 0:
            m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Front, rotation, ANGLE, ROTATION_SPEED));
            break;

        case 1:
            m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Back, rotation, ANGLE, ROTATION_SPEED));
            break;

        case 2:
            m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Up, rotation, ANGLE, ROTATION_SPEED));
            break;

        case 3:
            m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Down, rotation, ANGLE, ROTATION_SPEED));
            break;

        case 4:
            m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Left, rotation, ANGLE, ROTATION_SPEED));
            break;

        case 5:
            m_Tasks.emplace_back(std::make_unique<FaceRotation>(*this, m_Right, rotation, ANGLE, ROTATION_SPEED));
            break;
        }
    }
}

void RubiksCube::RotateFace(EFace face, ERotation rotation) {
    // Add task to queue
}

void RubiksCube::RotateCube(EDirection direction) {
    // Add task to queue
}

