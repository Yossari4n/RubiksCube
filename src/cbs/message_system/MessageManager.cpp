#include "MessageManager.h"

void MessageManager::Disconnect(IMessageOut* sender, IMessageIn* receiver) {
    m_MessageConnections[sender].erase(std::remove(m_MessageConnections[sender].begin(), m_MessageConnections[sender].end(), receiver));
}

void MessageManager::ForwardMessage(IMessageOut* sender, void* message) {
    for (auto it = m_MessageConnections[sender].begin(); it != m_MessageConnections[sender].end(); ++it) {
        (*it)->Receive(message);
    }
}
