#include "DummyComp.h"

DummyComp::DummyComp()
    : m_MessageOut(this)
    , m_MessageIn(this)
    , m_Message("Message test") {
}

void DummyComp::Initialize() {
    m_MessageOut.Send(m_Message);
}

void DummyComp::OnMessage(std::string msg) {
    std::cout << msg << '\n';
}