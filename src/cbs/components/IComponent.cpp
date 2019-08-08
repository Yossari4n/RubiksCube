#include "IComponent.h"

#include "../Object.h"

void IComponent::RegisterUpdateCall() const {
    m_Object->RegisterUpdateCall(this);
}