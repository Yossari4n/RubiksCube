#include "MessageManager.h"

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

    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](PropertyConnection_t& conn) { 
                                                   if (conn.second->m_Owner->ID() == comp_id) {
                                                       conn.second->Reset();
                                                       return true;
                                                   } else if (conn.first->m_Owner->ID() == comp_id) {
                                                       return true;
                                                   }
                                                   return false; }));
}
