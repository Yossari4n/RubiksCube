#ifndef TextRenderer_h
#define TextRenderer_h

#include "IComponent.h"
#include "../../rendering/IWidget.h"
#include "../Object.h"
#include "../../scenes/IScene.h"
#include "../message_system/MessageIn.h"

#include <string>

class TextRenderer : public IComponent, public IWidget {
public:
    TextRenderer(const std::string& text = "", ImVec2 offset = ImVec2(0.0f, 0.0f), EAlign vertical = EAlign::NONE, EAlign horizontal = EAlign::NONE);

    void Initialize() override;
    void Destroy() override;

    void Draw() const override;

private:
    void OnTextChanged(std::string text);

public:
    MessageIn<std::string, TextRenderer, & TextRenderer::OnTextChanged> ChangeText {this};

private:
    std::string m_Text;

    EAlign m_Horizontal;
    EAlign m_Vertical;
    ImVec2 m_Offset;
};

#endif