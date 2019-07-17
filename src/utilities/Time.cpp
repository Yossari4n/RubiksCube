#include "Time.h"

Time::Time()
    : m_CurrentTime(0.0f)
    , m_FixedCurrentTime(0.0f)
    , m_DeltaTime(0.0f)
    , m_FixedDeltaTime(0.0f)
    , m_LastFrame(0.0f)
    , m_TimeMultiplier(1) {
}

void Time::Initialize() {
    m_CurrentTime = static_cast<float>(glfwGetTime());
    m_LastFrame = m_FixedCurrentTime = m_CurrentTime;
}

void Time::Hold() {
    m_DeltaTime = static_cast<float>(glfwGetTime()) - m_LastFrame;
}

void Time::Update() {
    m_CurrentTime = static_cast<float>(glfwGetTime());
    
    // Absolute time calculations
    m_DeltaTime = m_CurrentTime - m_LastFrame;
    m_LastFrame = m_CurrentTime;
    
    // Relative time calculations
    m_FixedDeltaTime = m_DeltaTime * m_TimeMultiplier;
    m_FixedCurrentTime +=  m_FixedDeltaTime;
}

void Time::TimeMultiplayer(unsigned int time_multiplayer) {
    m_TimeMultiplier = time_multiplayer;
}
