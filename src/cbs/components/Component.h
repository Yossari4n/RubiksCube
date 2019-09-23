#ifndef Component_h
#define Component_h

#include <iostream>
#include <vector>
#include <algorithm>

class Object;
class ConnectionPipe;
class MessageManager;

class Component {
    friend class Object;

public:
    Component() = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component(Component&&) = delete;
    Component& operator=(Component&&) = delete;
    virtual ~Component() = default;

    std::uint8_t ID() const { return m_ID; }
    Object& Object() const { return *m_Object; }

protected:
    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Destroy() {};
    virtual void MakeConnectors(MessageManager& message_manager) { (void)message_manager; };

    void RegisterUpdateCall() const;
    void UnregisterUpdateCall() const;

private:
    class Object* m_Object{ nullptr };
    std::uint8_t m_ID{ 0 };
};

#endif
