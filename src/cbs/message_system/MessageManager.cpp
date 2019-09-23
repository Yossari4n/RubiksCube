#include "MessageManager.h"

#include "../components/Component.h"


void MessageManager::Make(Component* owner, TriggerOut& to_make) {
    to_make = TriggerOut(owner, this);
}

void MessageManager::ForwardMessage(AbstractMessageOut* sender, void* message) {
    for (auto it = m_MessageConnections[sender].begin(); it != m_MessageConnections[sender].end(); it++) {
        (*it)->Receive(message);
    }
}

void MessageManager::ForwardTrigger(AbstractTriggerOut* sender) {
    for (auto it = m_TriggerConnections[sender].begin(); it != m_TriggerConnections[sender].end(); it++) {
        (*it)->Receive();
    }
}

// TODO docs
void MessageManager::RemoveConnections(Component* component) {
    std::uint8_t comp_id = component->ID();

    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](std::pair<AbstractPropertyOut*, AbstractPropertyIn*>& conn) {
                                                   if (conn.second->Owner()->ID() == comp_id) {
                                                       return true;
                                                   } else if (conn.first->Owner()->ID() == comp_id) {
                                                       conn.second->RemoveSource();
                                                       return true;
                                                   }
                                                   return false; }),
                                m_PropertyConnections.end());

    for (auto it = m_MessageConnections.begin(); it != m_MessageConnections.end(); ) {
        if (it->first->Owner()->ID() == comp_id) {
            m_MessageConnections.erase(it++);
        } else {
            it->second.erase(std::remove_if(it->second.begin(),
                                            it->second.end(),
                                            [=](auto receiver) { return receiver->Owner()->ID() == comp_id; }),
                             it->second.end());
            it++;
        }
    }

    for (auto it = m_TriggerConnections.begin(); it != m_TriggerConnections.end(); ) {
        if (it->first->Owner()->ID() == comp_id) {
            m_TriggerConnections.erase(it++);
        } else {
            it->second.erase(std::remove_if(it->second.begin(),
                                            it->second.end(),
                                            [=](auto receiver) { return receiver->Owner()->ID() == comp_id; }),
                             it->second.end());
            it++;
        }
    }
}
