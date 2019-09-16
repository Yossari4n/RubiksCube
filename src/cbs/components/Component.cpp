#include "Component.h"

#include "../Object.h"

Component::Component(class Object& owner)
    : m_Object(owner) {

}

void Component::RegisterUpdateCall() const {
    m_Object.RegisterUpdateCall(this);
}

void Component::UnregisterUpdateCall() const {
    m_Object.UnregisterUpdateCall(this);
}
