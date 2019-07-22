#include "DummyComp.h"

DummyComp::DummyComp()
    : m_MessageOut(this)
    , m_MessageIn(this)
    , m_Message("Message test") {
}

void DummyComp::Update() {
    if (g_Input.GetKeyState(GLFW_MOUSE_BUTTON_1) == Input::KeyState::PRESSED) {
        m_MessageOut.Send(m_Message);
    }
    if (g_Input.GetKeyState(GLFW_MOUSE_BUTTON_2) == Input::KeyState::PRESSED) {
        Object().RemoveComponent(3);
    }
}

void DummyComp::OnMessage(std::string msg) {
    std::cout << msg << '\n';
}