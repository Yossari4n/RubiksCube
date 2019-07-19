#ifndef DummyComp_h
#define DummyComp_h

#include "IComponent.h"
#include "../Object.h"
#include "../message_system/MessageOut.h"
#include "../message_system/MessageIn.h"

#include <iostream>
#include <string>

class DummyComp : public IComponent {
public:
    DummyComp();

    void Initialize() override;

    void OnMessage(std::string msg);

    MessageOut<std::string> m_MessageOut;

    MessageIn<std::string, DummyComp, &DummyComp::OnMessage> m_MessageIn;

private:
    std::string m_Message;
};

#endif