#ifndef Time_h
#define Time_h

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

constexpr auto FPS_LIMIT30 = (1.0f / 30.0f);
constexpr auto FPS_LIMIT60 = (1.0f / 60.0f);
constexpr auto FPS_LIMIT300 = (1.0f / 300.0f);

class Time {
public:
    Time();
    
    void Initialize();
    void Hold();
    void Update();
    
    float CurrentTime() const { return m_CurrentTime; }
    float FixedCurrentTime() const { return m_FixedCurrentTime; }
    float DeltaTime() const { return m_DeltaTime; }
    float FixedDeltaTime() const { return m_FixedDeltaTime; }
    
    unsigned int TimeMultiplayer() const { return m_TimeMultiplier; }
    void TimeMultiplayer(unsigned int time_multiplayer);
    
private:
    float m_CurrentTime;
    float m_FixedCurrentTime;
    float m_DeltaTime;
    float m_FixedDeltaTime;
    float m_LastFrame;
    unsigned int m_TimeMultiplier;
};

extern Time g_Time;

#endif
