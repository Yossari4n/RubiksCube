#include "DummyComp.h"

DummyComp::DummyComp()
    : m_MessageOut(this)
    , m_MessageIn(this)
    , m_Message("Message test") {
}

DummyComp::~DummyComp() {
    std::cout << "Dest " << static_cast<int>(ID()) << '\n';
}

void DummyComp::Initialize() {
    std::cout << "Init " << static_cast<int>(ID()) << '\n';

    if (ID() == 3) {
        Object().CreateComponent<DummyComp>();
    }
}

void DummyComp::Update() {
    if (g_Input.GetKeyState(GLFW_MOUSE_BUTTON_1) == Input::KeyState::PRESSED) {
        m_MessageOut.Send(m_Message);
    }
    if (g_Input.GetKeyState(GLFW_MOUSE_BUTTON_2) == Input::KeyState::PRESSED) {
        Object().RemoveComponent(4);
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