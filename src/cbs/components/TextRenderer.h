#ifndef TextRenderer_h
#define TextRenderer_h

#include "Component.h"
#include "../../rendering/IWidget.h"
#include "../Object.h"
#include "../../scenes/Scene.h"
#include "../message_system/MessageIn.h"

#include <string>

class TextRenderer : public Component, public IWidget {
public:
    TextRenderer(const std::string& text = "", glm::vec2 offset = glm::vec2(0.0f, 0.0f), EAlign vertical = EAlign::NONE, EAlign horizontal = EAlign::NONE);

    void Initialize() override;
    void Destroy() override;

    void Draw() const override;

    void ChangeFont(std::string path, float size);
    void ChangeText(std::string text);
    void ChangeColor(glm::vec4 color);

public:
    // TODO ChangeFontIn
    MessageIn<std::string, TextRenderer, &TextRenderer::ChangeText> ChangeTextIn { this };
    MessageIn<glm::vec4, TextRenderer, &TextRenderer::ChangeColor> ChangeColorIn { this };

private:
    std::string m_Text;

    EAlign m_Horizontal;
    EAlign m_Vertical;
    glm::vec2 m_Offset;
    glm::vec4 m_Color;
    ImFont* m_Font;
};

#endif