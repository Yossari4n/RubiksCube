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
RubiksCube::Face RubiksCube::s_Front {
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

RubiksCube::Face RubiksCube::s_Back {
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

RubiksCube::Face RubiksCube::s_Left {
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

RubiksCube::Face RubiksCube::s_Right {
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

RubiksCube::Face RubiksCube::s_Up {
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

RubiksCube::Face RubiksCube::s_Down {
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
    const float rotation_speed = 2.0f;
    const unsigned int randomize_moves = 30;

    // Collect next move 
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_F) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Front, 90.0f, "F'", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_F) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Front, -90.0f, "F", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Back, 90.0f, "B'", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Back, -90.0f, "B", rotation_speed);
    } if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_L) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Left, 90.0f, "L'", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_L) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Left, -90.0f, "L", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_R) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Right, 90.0f, "R'", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_R) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Right, -90.0f, "R", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_U) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Up, 90.0f, "U'", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_U) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Up, -90.0f, "U", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT) == Input::KeyState::HOLD && g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Down, 90.0f, "D'", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        m_Tasks.emplace_back(*this, s_Down, -90.0f, "D", rotation_speed);
    } else if (g_Input.GetKeyState(GLFW_KEY_UP) == Input::KeyState::PRESSED) {
        RotateCube(1);
    } else if (g_Input.GetKeyState(GLFW_KEY_DOWN) == Input::KeyState::PRESSED) {
        RotateCube(2);
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT) == Input::KeyState::PRESSED) {
        RotateCube(3);
    } else if (g_Input.GetKeyState(GLFW_KEY_RIGHT) == Input::KeyState::PRESSED) {
        RotateCube(4);
    }

    // Update deque of tasks
    if (!m_Tasks.empty()) {
        if (!m_Tasks.front().Finished()) {
            m_Tasks.front().RotateOverTime(g_Time.FixedDeltaTime());
        } else {
            m_Tasks.pop_front();
        }

        std::string message = "";
        for (auto it = m_Tasks.begin(); it != m_Tasks.end(); it++) {
            message += ' ' + it->Signature();
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
    const float rotation_speed = 3.0f;

    if (m_Tasks.size() > 0) {
        // Finish current task
        m_Tasks.front().RotateOverTime(1.0f);
        
        m_Tasks.clear();
    }

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 5);
    for (unsigned int i = 0; i < moves; i++) {
        int rn = distribution(generator);

        // 50% chances for clockwise and 50% chances for counter-clockwise rotation
        float angle = 90.0f;
        if (rn % 2 == 0) {
            angle = -90.0f;
        }

        // Each face has equal chance to be choosen
        switch (rn) {
        case 0:
            m_Tasks.emplace_back(*this, s_Front, angle, "", rotation_speed);
            break;

        case 1:
            m_Tasks.emplace_back(*this, s_Back, angle, "", rotation_speed);
            break;

        case 2:
            m_Tasks.emplace_back(*this, s_Up, angle, "", rotation_speed);
            break;

        case 3:
            m_Tasks.emplace_back(*this, s_Down, angle, "", rotation_speed);
            break;

        case 4:
            m_Tasks.emplace_back(*this, s_Left, angle, "", rotation_speed);
            break;

        case 5:
            m_Tasks.emplace_back(*this, s_Right, angle, "", rotation_speed);
            break;
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

void RubiksCube::RotateCube(int direction) {
    if (direction == 1) {
        Object().Root().Rotate(glm::vec3(0.0f, 0.0f, glm::radians(90.0f)));

        // left.cubies = front.cubies; front.cubies = right.cubies; etc
    } else if (direction == 2) {
        Object().Root().Rotate(glm::vec3(0.0f, 0.0f, glm::radians(-90.0f)));
    } else if (direction == 3) {
        Object().Root().Rotate(glm::vec3(0.0f, glm::radians(-90.0f), 0.0f));
    } else if (direction == 4) {
        Object().Root().Rotate(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
    }
}



RubiksCube::Task::Task(RubiksCube& owner, const RubiksCube::Face& face, float target, const std::string& signature, float rotation_speed)
    : m_Owner(owner)
    , m_Face(face)
    , m_TargetAngle(target)
    , m_Progress(0.0f)
    , m_Finished(false)
    , m_Signature(signature)
    , m_RotationSpeed(rotation_speed) {
}

void RubiksCube::Task::RotateOverTime(float delta) {
    // Task already finished
    if (m_Finished) {
        return;
    }
    
    const float new_angle = m_RotationSpeed * delta * m_TargetAngle;
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
