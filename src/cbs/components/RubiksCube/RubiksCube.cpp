#include "RubiksCube.h"

RubiksCube::RubiksCube() {
    m_Cubies.reserve(26);

    // Front
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::BLUE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED);
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, 1.0f), Cubie::EColor::BLUE, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, -1.0f), Cubie::EColor::BLUE, Cubie::EColor::BLACK, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);

    // Back
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::GREEN);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, 1.0f), Cubie::EColor::GREEN, Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, -1.0f), Cubie::EColor::GREEN, Cubie::EColor::BLACK, Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);
    for (auto it = m_Cubies.begin() + 9; it != m_Cubies.end(); it++) {
        it->RotateAround(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Left
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::RED);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::RED, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);
    for (auto it = m_Cubies.begin() + 18; it != m_Cubies.end(); it++) {
        it->RotateAround(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Right
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::ORANGE);
    m_Cubies.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f), Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::WHITE);
    m_Cubies.emplace_back(glm::vec3(1.0f, -1.0f, 0.0f), Cubie::EColor::ORANGE, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::BLACK, Cubie::EColor::YELLOW);
    for (auto it = m_Cubies.begin() + 21; it != m_Cubies.end(); it++) {
        it->RotateAround(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Top
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::WHITE);
    (m_Cubies.end() - 1)->RotateAround(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    // Bottom
    m_Cubies.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f), Cubie::EColor::YELLOW);
    (m_Cubies.end() - 1)->RotateAround(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void RubiksCube::Initialize() {
    for (auto it = m_Cubies.begin(); it != m_Cubies.end(); it++) {
        Object().Scene().RegisterDrawCall(&*it);
    }
}

void RubiksCube::Destroy() {
    for (auto it = m_Cubies.begin(); it != m_Cubies.end(); it++) {
        Object().Scene().UnregisterDrawCall(&*it);
    }
}