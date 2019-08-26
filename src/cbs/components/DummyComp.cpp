#include "DummyComp.h"

DummyComp::DummyComp()
    : m_Message("Message test") {
}

DummyComp::~DummyComp() {
}

void DummyComp::Initialize() {
    RegisterUpdateCall();
}

void DummyComp::Update() {
    if (g_Input.GetKeyState(GLFW_KEY_SPACE) == Input::KeyState::PRESSED) {
        m_TriggerOut.Trigger();
    }

    if (g_Input.GetKeyState(GLFW_KEY_ESCAPE)) {
        Object().Scene().Exit();
    }
}

void DummyComp::Destroy() {
}

void DummyComp::OnMessage(std::string msg) {
}

void DummyComp::OnTrigger() {
    std::cout << "Trigger!\n";
    Object().RemoveComponent(ID()); 
}
