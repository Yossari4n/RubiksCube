#include "MessageManager.h"

void MessageManager::Disconnect(IPropertyOut* subject, IPropertyIn* observer) {

}

void MessageManager::Disconnect(IMessageOut* sender, IMessageIn* receiver) {
    m_MessageConnections[sender].erase(std::remove(m_MessageConnections[sender].begin(), m_MessageConnections[sender].end(), receiver));
}

void MessageManager::ForwardMessage(IMessageOut* sender, void* message) {
    for (auto it = m_MessageConnections[sender].cbegin(); it != m_MessageConnections[sender].cend(); ++it) {
        (*it)->Receive(message);
    }
}

void MessageManager::RemoveConnections(IComponent* component) {
    std::uint8_t comp_id = component->ID();

    for (auto it = m_MessageConnections.begin(); it != m_MessageConnections.end(); ) {
        if (it->first->m_Owner->ID() == comp_id) {
            m_MessageConnections.erase(it++);
        } else {
            it->second.erase(std::remove_if(it->second.begin(),
                                              it->second.end(),
                                              [=](auto receiver) { return receiver->m_Owner->ID() == comp_id; }));
            ++it;
        }
    }
}
