#include "Component.h"

#include "../Object.h"
#include "../message_system/ConnectionInterfaces.h"

void Component::RegisterUpdateCall() const {
    m_Object->RegisterUpdateCall(this);
}

void Component::UnregisterUpdateCall() const {
    m_Object->UnregisterUpdateCall(this);
}

void Component::RegisterConnector(ConnectionPipe& pipe) {
    assert(std::find(m_ConnectionPipes.begin(), m_ConnectionPipes.end(), &pipe) == m_ConnectionPipes.end());

    m_ConnectionPipes.push_back(&pipe);
}
