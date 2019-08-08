#include "DummyComp.h"

DummyComp::DummyComp()
    : m_MessageOut(this)
    , m_MessageIn(this)
    , m_PropertyOut(this, 0.0f)
    , m_PropertyIn(this)
    , m_Message("Message test") {
}

DummyComp::~DummyComp() {
}

void DummyComp::Initialize() {
    RegisterUpdateCall();
}

void DummyComp::Update() {
    if (g_Input.GetKeyState(GLFW_KEY_SPACE) == Input::KeyState::PRESSED) {
        Object().UnregisterUpdateCall(this);
    }
    
    if (g_Input.GetKeyState(GLFW_KEY_ESCAPE)) {
        Object().Scene().Exit();
    }
}

void DummyComp::Destroy() {
}

void DummyComp::OnMessage(std::string msg) {
}
