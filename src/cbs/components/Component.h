#ifndef Component_h
#define Component_h

#include <iostream>
#include <vector>
#include <algorithm>

class Object;
class ConnectionPipe;

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

    void RegisterUpdateCall() const;
    void UnregisterUpdateCall() const;

    void RegisterConnection(ConnectionPipe& pipe);

private:
    class Object* m_Object{ nullptr };
    std::uint8_t m_ID{ 0 };

    std::vector<ConnectionPipe*> m_ConnectionPipes;
};

#endif
