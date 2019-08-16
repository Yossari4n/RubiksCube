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

    void ChangeFont(std::string path, float size);
    void ChangeText(std::string text);
    void ChangeColor(ImVec4 color);

public:
    // TODO ChangeFontIn
    MessageIn<std::string, TextRenderer, &TextRenderer::ChangeText> ChangeTextIn { this };
    MessageIn<ImVec4, TextRenderer, &TextRenderer::ChangeColor> ChangeColorIn { this };

private:
    std::string m_Text;

    EAlign m_Horizontal;
    EAlign m_Vertical;
    ImVec2 m_Offset;
    ImVec4 m_Color;
    ImFont* m_Font;
};

#endif