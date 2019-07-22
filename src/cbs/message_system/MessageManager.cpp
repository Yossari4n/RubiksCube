#include "MessageManager.h"

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

    for (auto pair = m_MessageConnections.begin(); pair != m_MessageConnections.end(); ) {
        if (pair->first->m_Owner->ID() == comp_id) {
            m_MessageConnections.erase(pair++);
        } else {
            pair->second.erase(std::remove_if(pair->second.begin(),
                                              pair->second.end(),
                                              [=](auto receiver) { return receiver->m_Owner->ID() == comp_id; }));
            ++pair;
        }
    }
}
