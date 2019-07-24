#include "DummyComp.h"

DummyComp::DummyComp()
    : m_MessageOut(this)
    , m_MessageIn(this)
    , m_PropertyOut(this, 0.0f)
    , m_PropertyIn(this)
    , m_Message("Message test") {
}

DummyComp::~DummyComp() {
    std::cout << "Dest " << static_cast<int>(ID()) << '\n';
}

void DummyComp::Initialize() {
    std::cout << "Init " << static_cast<int>(ID()) << '\n';
}

void DummyComp::Update() {
    if (g_Input.GetKeyState(GLFW_MOUSE_BUTTON_1) == Input::KeyState::PRESSED) {
        m_MessageOut.Send(m_Message);
    }

    if (g_Input.GetKeyState(GLFW_KEY_A) == Input::KeyState::PRESSED) {
        m_PropertyOut = m_PropertyOut + 1;
    }

    if (g_Input.GetKeyState(GLFW_KEY_D) == Input::KeyState::PRESSED) {
        std::cout << m_PropertyIn << '\n';
    }

    if (g_Input.GetKeyState(GLFW_KEY_ESCAPE)) {
        Object().Scene().Exit();
    }
}

void DummyComp::Destroy() {
    std::cout << "Destroy " << static_cast<int>(ID()) << '\n';
}

void DummyComp::OnMessage(std::string msg) {
    std::cout << msg << '\n';
}