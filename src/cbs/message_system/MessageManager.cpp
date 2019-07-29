#include "MessageManager.h"

void MessageManager::UnsafeConnect(IPropertyOut* subject, IPropertyIn* observer) {
    m_PropertyConnections.emplace_back(subject, observer);
}

void MessageManager::UnsafeDisconnect(IPropertyOut* subject, IPropertyIn* observer) {
    m_PropertyConnections.erase(std::remove_if(m_PropertyConnections.begin(),
                                               m_PropertyConnections.end(),
                                               [=](std::pair<IPropertyOut*, IPropertyIn*>& pair) { 
                                                   if (pair.first == subject && pair.second == observer) {
                                                       pair.second->Reset();
                                                       return true;
                                                   }
                                                   return false; }));
}

void MessageManager::UnsafeConnect(IMessageOut* sender, IMessageIn* receiver) {
    sender->m_MessageManager = this;
    receiver->m_MessageManager = this;
    m_MessageConnections[sender].push_back(receiver);
}

void MessageManager::UnsafeDisconnect(IMessageOut* sender, IMessageIn* receiver) {
    m_MessageConnections[sender].erase(std::remove(m_MessageConnections[sender].begin(), 
                                                   m_MessageConnections[sender].end(), 
                                                   receiver));
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
