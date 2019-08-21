#include "RubiksCube.h"

std::ostream& operator<<(std::ostream& os, RubiksCube::ERotation dir) {
    if (dir == RubiksCube::ERotation::CLOCKWISE) {
        os << "Clockwise";
    } else {
        os << "Counter-clodkwise";
    }
    return os;
}


#pragma region Faces
RubiksCube::Face RubiksCube::s_Front = {
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
    { glm::vec3(1.0f, 0.0f, 0.0f) }
};

RubiksCube::Face RubiksCube::s_Back = {
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
    { glm::vec3(-1.0f, 0.0f, 0.0f) }
};

RubiksCube::Face RubiksCube::s_Left = {
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
    { glm::vec3(0.0f, 0.0f, 1.0f) }
};

RubiksCube::Face RubiksCube::s_Right = {
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
    { glm::vec3(0.0f, 0.0f, -1.0f) }
};

RubiksCube::Face RubiksCube::s_Up = {
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
    { glm::vec3(0.0f, 1.0f, 0.0f) }
};

RubiksCube::Face RubiksCube::s_Down = {
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
    { glm::vec3(0.0f, -1.0f, 0.0f) }
};
#pragma endregion

RubiksCube::RubiksCube() {
    for (int matrix = 0; matrix < 3; matrix++) {
        m_Cube.emplace_back();
        for (int row = 0; row < 3; row++) {
            m_Cube[matrix].emplace_back();
            m_Cube[matrix][row].reserve(3);
        }
    }
    
    // Front face
    // First row
    m_Cube[0][0].emplace_back(new Cubie(glm::vec3(1.0f, 1.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::WHITE));
    m_Cube[0][0].emplace_back(new Cubie(glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE));
    m_Cube[0][0].emplace_back(new Cubie(glm::vec3(1.0f, 1.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE, Cubie::EColor::WHITE));
    // Second row
    m_Cube[0][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED));
    m_Cube[0][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::BLUE));
    m_Cube[0][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE));
    // Third row
    m_Cube[0][2].emplace_back(new Cubie(glm::vec3(1.0f, -1.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[0][2].emplace_back(new Cubie(glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[0][2].emplace_back(new Cubie(glm::vec3(1.0f, -1.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));

    // Back face
    // First row
    m_Cube[2][0].emplace_back(new Cubie(glm::vec3(1.0f, 1.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED, Cubie::EColor::WHITE));
    m_Cube[2][0].emplace_back(new Cubie(glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE));
    m_Cube[2][0].emplace_back(new Cubie(glm::vec3(1.0f, 1.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::WHITE));

    // Second row
    m_Cube[2][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED));
    m_Cube[2][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::GREEN));
    m_Cube[2][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE));

    // Third row
    m_Cube[2][2].emplace_back(new Cubie(glm::vec3(1.0f, -1.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[2][2].emplace_back(new Cubie(glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    m_Cube[2][2].emplace_back(new Cubie(glm::vec3(1.0f, -1.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW));
    for (auto row = m_Cube[2].begin(); row != m_Cube[2].end(); row++) {
        for (auto cubie = row->begin(); cubie != row->end(); cubie++) {
            (*cubie)->RotateAround(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
    
    // Middle face
    // First row
    m_Cube[1][0].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::WHITE, Cubie::EColor::RED))->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));;
    m_Cube[1][0].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::WHITE))->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));;
    m_Cube[1][0].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::WHITE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE))->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));;

    // Second row
    m_Cube[1][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::RED))->RotateAround(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_Cube[1][1].emplace_back(new Cubie(glm::vec3(0.0f, 0.0f, 0.0f), Cubie::EColor::BLACK)); // Hidden cubie in the center
    m_Cube[1][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::ORANGE))->RotateAround(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Third row
    m_Cube[1][2].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::YELLOW, Cubie::EColor::RED))->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    m_Cube[1][2].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::YELLOW))->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    m_Cube[1][2].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::YELLOW, Cubie::EColor::BLACK, Cubie::EColor::ORANGE))->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void RubiksCube::Initialize() {
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
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_F) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Front, 90.0f, "F'");
    } else if (g_Input.GetKeyState(GLFW_KEY_F) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Front, -90.0f, "F");
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Back, 90.0f, "B'");
    } else if (g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Back, -90.0f, "B");
    } if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_L) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Left, 90.0f, "L'");
    } else if (g_Input.GetKeyState(GLFW_KEY_L) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Left, -90.0f, "L");
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_R) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Right, 90.0f, "R'");
    } else if (g_Input.GetKeyState(GLFW_KEY_R) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Right, -90.0f, "R");
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_U) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Up, 90.0f, "U'");
    } else if (g_Input.GetKeyState(GLFW_KEY_U) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Up, -90.0f, "U");
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Down, 90.0f, "D'");
    } else if (g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Down, -90.0f, "D");
    }

    if (!m_Tasks.empty()) {
        std::string message;
        for (auto it = m_Tasks.begin(); it != m_Tasks.end(); it++) {
            message += it->Signature() + ' ';
        }
        TasksSignaturesOut.Send(message);

        if (!m_Tasks.front().Finished()) {
            m_Tasks.front().RotateOverTime(g_Time.FixedDeltaTime());
        } else {
            m_Tasks.pop_front();
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

void RubiksCube::RotateMeshes(const Face& face, float angle) {
    for (int i = 0; i < 8; i++) {
        m_Cube[face.CubiesAround[i][0]][face.CubiesAround[i][1]][face.CubiesAround[i][2]]->RotateAround(angle, face.Axis);
    }
    m_Cube[face.Center[0]][face.Center[1]][face.Center[2]]->RotateAround(angle, face.Axis);
}

void RubiksCube::RotateData(const Face& face, RubiksCube::ERotation rotation) {
    // GCD left-shift array shift
    const int size = 8;
    const int shift = rotation == ERotation::CLOCKWISE ? 6 : 2; // For clockwise rotation right-shift by 2 is equal to left-shift by 6. For counter clockwise rotation left-shift by 2.
    const int gcd = 2;                                          // gcd(2, 8) = gcd(6, 8) = 2
    for (int i = 0; i < gcd; i++) {
        Cubie* tmp = m_Cube[face.CubiesAround[i][0]][face.CubiesAround[i][1]][face.CubiesAround[i][2]];
        int j = i;

        while (true) {
            int k = j + shift;
            if (k >= size) {
                k = k - size;
            }
            if (k == i) {
                break;
            }

            m_Cube[face.CubiesAround[j][0]][face.CubiesAround[j][1]][face.CubiesAround[j][2]] = m_Cube[face.CubiesAround[k][0]][face.CubiesAround[k][1]][face.CubiesAround[k][2]];
            j = k;
        }
        m_Cube[face.CubiesAround[j][0]][face.CubiesAround[j][1]][face.CubiesAround[j][2]] = tmp;
    }
}

RubiksCube::Task::Task(RubiksCube& owner, const RubiksCube::Face& face, float target, std::string signature)
    : m_Owner(owner)
    , m_Face(face)
    , m_TargetAngle(target)
    , m_Progress(0.0f)
    , m_Finished(false)
    , m_Signature(signature) {
}

void RubiksCube::Task::RotateOverTime(float delta) {
    // Task already finished
    if (m_Finished) {
        return;
    }
    
    const float new_angle = delta * m_TargetAngle;
    if (abs(m_Progress + new_angle) > abs(m_TargetAngle)) {
        // On task finished
        m_Owner.RotateMeshes(m_Face, m_TargetAngle - m_Progress);
        m_Owner.RotateData(m_Face, m_TargetAngle < 0.0f ? ERotation::CLOCKWISE : ERotation::COUNTER_CLOCKWISE);
        m_Finished = true;
    } else {
        // Continue on task
        m_Progress = m_Progress + new_angle;
        m_Owner.RotateMeshes(m_Face, new_angle);
    }
}
