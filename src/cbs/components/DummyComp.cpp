#include "DummyComp.h"

void DummyComp::Initialize() {
    RegisterUpdateCall();
}

void DummyComp::Update() {

    if (g_Input.KeyPressed(GLFW_KEY_SPACE)) {
        m_TriggerOut.Trigger();
    }

    if (g_Input.KeyPressed(GLFW_KEY_ESCAPE)) {
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
