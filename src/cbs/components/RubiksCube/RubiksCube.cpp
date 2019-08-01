#include "RubiksCube.h"

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
    m_Cube[1][0].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::WHITE, Cubie::EColor::RED));
    m_Cube[1][0].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::WHITE));
    m_Cube[1][0].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::WHITE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE));
    for (auto cubie = m_Cube[1][0].begin(); cubie != m_Cube[1][0].end(); cubie++) {
        (*cubie)->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    // Second row
    m_Cube[1][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::RED));
    m_Cube[1][1].emplace_back(new Cubie(glm::vec3(0.0f, 0.0f, 0.0f), Cubie::EColor::BLACK)); // Hidden cubie in the center
    m_Cube[1][1].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::ORANGE));
    m_Cube[1][1][0]->RotateAround(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_Cube[1][1][2]->RotateAround(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Third row
    m_Cube[1][2].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::YELLOW, Cubie::EColor::RED));
    m_Cube[1][2].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::YELLOW));
    m_Cube[1][2].emplace_back(new Cubie(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::YELLOW, Cubie::EColor::BLACK, Cubie::EColor::ORANGE));
    for (auto cubie = m_Cube[1][2].begin(); cubie != m_Cube[1][2].end(); cubie++) {
        (*cubie)->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    int id = 1;
    for (auto matrix = m_Cube.begin(); matrix != m_Cube.end(); matrix++) {
        for (auto row = matrix->begin(); row != matrix->end(); row++) {
            for (auto cube = row->begin(); cube != row->end(); cube++) {
                (*cube)->m_ID = id;
                id++;
            }
        }
    }

    std::cout << "Cube:\n";
    Print();
}

void RubiksCube::Initialize() {
    for (auto matrix = m_Cube.begin(); matrix != m_Cube.end(); matrix++) {
        for (auto row = matrix->begin(); row != matrix->end(); row++) {
            for (auto cube = row->begin(); cube != row->end(); cube++) {
                Object().Scene().RegisterDrawCall(*cube);
            }
        }
    }
}

void RubiksCube::Update() {
    if (g_Input.GetKeyState(GLFW_KEY_F) == Input::KeyState::PRESSED) {
        RotateFront(1);
    } else if (g_Input.GetKeyState(GLFW_KEY_L) == Input::KeyState::PRESSED) {
        RotateLeft(1);
    } else if (g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        RotateBack(1);
    } else if (g_Input.GetKeyState(GLFW_KEY_R) == Input::KeyState::PRESSED) {
        RotateRight(1);
    } else if (g_Input.GetKeyState(GLFW_KEY_U) == Input::KeyState::PRESSED) {
        RotateUp(1);
    } else if (g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        RotateDown(1);
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

void RubiksCube::Print() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                std::cout << m_Cube[j][i][k]->m_ID << ' ';
            }
            std::cout << "| ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void RubiksCube::RotateFront(int direction) {
    const size_t front[8][3] = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 0, 2},
        {0, 1, 2},
        {0, 2, 2},
        {0, 2, 1},
        {0, 2, 0},
        {0, 1, 0},
    };

    std::cout << "Rotating front:\n";
    RotateFace(front, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void RubiksCube::RotateBack(int direction) {
    const size_t back[8][3] = {
        {2, 0, 2},
        {2, 0, 1},
        {2, 0, 0},
        {2, 1, 0},
        {2, 2, 0},
        {2, 2, 1},
        {2, 2, 2},
        {2, 1, 2},
    };

    std::cout << "Rotating right:\n";
    RotateFace(back, 90.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
}

void RubiksCube::RotateLeft(int direction) {
    const size_t left[8][3] = {
        {2, 0, 0},
        {1, 0, 0},
        {0, 0, 0},
        {0, 1, 0},
        {0, 2, 0},
        {1, 2, 0},
        {2, 2, 0},
        {2, 1, 0}
    };

    std::cout << "Rotating left:\n";
    RotateFace(left, -90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void RubiksCube::RotateRight(int direction) {
    const size_t right[8][3] = {
        {0, 0, 2},
        {1, 0, 2},
        {2, 0, 2},
        {2, 1, 2},
        {2, 2, 2},
        {1, 2, 2},
        {0, 2, 2},
        {0, 1, 2}
    };

    std::cout << "Rotation right:\n";
    RotateFace(right, -90.0f, glm::vec3(0.0f, 0.0f, -1.0f));
}

void RubiksCube::RotateUp(int direction) {
    const size_t top[8][3] = {
        {2, 0, 0},
        {2, 0, 1},
        {2, 0, 2},
        {1, 0, 2},
        {0, 0, 2},
        {0, 0, 1},
        {0, 0, 0},
        {1, 0, 0}
    };

    std::cout << "Rotatino up:\n";
    RotateFace(top, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void RubiksCube::RotateDown(int direction) {
    const size_t bottom[8][3] = {
        {0, 2, 2},
        {0, 2, 1},
        {0, 2, 0},
        {1, 2, 0},
        {2, 2, 0},
        {2, 2, 1},
        {2, 2, 2},
        {1, 2, 2}
    };

    std::cout << "Rotating down:\n";
    RotateFace(bottom, -90.0f, glm::vec3(0.0f, -1.0f, 0.0f));
}

int RubiksCube::gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

void RubiksCube::RotateFace(const size_t face[8][3], float angle, glm::vec3 axis) {
    std::cout << "Rotating cubies: ";
    for (int i = 0; i < 8; i++) {
        std::cout << m_Cube[face[i][0]][face[i][1]][face[i][2]]->m_ID << ' ';
    } 

    int g_c_d = gcd(2, 8);
    for (int i = 0; i < g_c_d; i++) {
        Cubie* tmp = m_Cube[face[i][0]][face[i][1]][face[i][2]];
        int j = i;

        while (true) {
            int k = j + 2;
            if (k >= 8) {
                k = k - 8;
            }
            if (k == i) {
                break;
            }

            m_Cube[face[j][0]][face[j][1]][face[j][2]] = m_Cube[face[k][0]][face[k][1]][face[k][2]];
            j = k;
        }
        m_Cube[face[j][0]][face[j][1]][face[j][2]] = tmp;
    }

    std::cout << "\nInto           : ";
    for (int i = 0; i < 8; i++) {
        std::cout << m_Cube[face[i][0]][face[i][1]][face[i][2]]->m_ID << ' ';
    }

    std::cout << "\nCube after rotation:\n";
    Print();

    for (int i = 0; i < 8; i++) {
        m_Cube[face[i][0]][face[i][1]][face[i][2]]->RotateAround(angle, axis);
    }
    std::cout << "\n\n";
}