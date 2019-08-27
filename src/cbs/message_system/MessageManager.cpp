#include "MessageManager.h"

void MessageManager::ForwardMessage(IMessageOut* sender, void* message) {
    for (auto it = m_MessageConnections[sender].begin(); it != m_MessageConnections[sender].end(); it++) {
        (*it)->Receive(message);
    }
}

void MessageManager::ForwardTrigger(ITriggerOut* sender) {
    for (auto it = m_TriggerConnections[sender].begin(); it != m_TriggerConnections[sender].end(); it++) {
        (*it)->Receive();
    }
}

// TODO more tests
void MessageManager::RemoveConnections(Component* component) {
    std::uint8_t comp_id = component->ID();

    // TODO doc
    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](std::pair<IPropertyOut*, IPropertyIn*>& conn) {
                                                   if (conn.second->m_Owner->ID() == comp_id) {
                                                       conn.second->Reset();
                                                       return true;
                                                   } else if (conn.first->m_Owner->ID() == comp_id) {
                                                       return true;
                                                   }
                                                   return false; }),
                                m_PropertyConnections.end());

    // TODO doc
    for (auto it = m_MessageConnections.begin(); it != m_MessageConnections.end(); ) {
        if (it->first->m_Owner->ID() == comp_id) {
            m_MessageConnections.erase(it++);
        } else {
            it->second.erase(std::remove_if(it->second.begin(),
                                            it->second.end(),
                                            [=](auto receiver) { return receiver->m_Owner->ID() == comp_id; }),
                             it->second.end());
            it++;
        }
    }

    // TODO doc
    for (auto it = m_TriggerConnections.begin(); it != m_TriggerConnections.end(); ) {
        if (it->first->m_Owner->ID() == comp_id) {
            m_TriggerConnections.erase(it++);
        } else {
            it->second.erase(std::remove_if(it->second.begin(),
                                            it->second.end(),
                                            [=](auto receiver) { return receiver->m_Owner->ID() == comp_id; }),
                             it->second.end());
            it++;
        }
    }
}
