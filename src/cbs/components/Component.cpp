#include "Component.h"

#include "../Object.h"

void Component::RegisterUpdateCall() const {
    m_Object->RegisterUpdateCall(this);
}