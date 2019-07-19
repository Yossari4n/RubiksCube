#include "MessageManager.h"

void MessageManager::ForwardMessage(IMessageOut* sender, void* message) {
    for (auto it = m_MessageConnections[sender].begin(); it != m_MessageConnections[sender].end(); ++it) {
        (*it)->Receive(message);
    }
}
