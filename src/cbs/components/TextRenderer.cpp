#include "TextRenderer.h"

TextRenderer::TextRenderer(const std::string& text, ImVec2 offset, EAlign horizontal, EAlign vertical)
    : m_Text(text)
    , m_Horizontal(horizontal)
    , m_Vertical(vertical) 
    , m_Offset(offset) {
    assert(offset.x >= 0.0f && offset.x <= 1.0f && offset.y >= 0.0f && offset.y <= 1.0f);
}

void TextRenderer::Initialize() {
    Object().Scene().RegisterWidget(this);
}

void TextRenderer::Destroy() {
    Object().Scene().UnregisterWidget(this);
}

void TextRenderer::Draw() const {
    ImGui::Begin("dummy", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize);

    ImVec2 pos(0.0f, 0.0f);
    const ImVec2 margin = ImGui::GetWindowContentRegionMin();       // Might not be correct
    const ImVec2 text_size = ImGui::CalcTextSize(m_Text.c_str());

    pos.x = pos.x + m_Offset.x * g_Window.Width();
    pos.y = pos.y + m_Offset.y * g_Window.Height();
    IWidget::Align(&pos.x, -margin.x / 2, g_Window.Width() - margin.x / 2 - text_size.x, m_Horizontal);
    IWidget::Align(&pos.y, -margin.y / 2, g_Window.Height() - margin.y / 2 - text_size.y, m_Vertical);

    ImGui::SetWindowPos(pos);
    ImGui::Text(m_Text.c_str());

    ImGui::End();
}

void TextRenderer::OnTextChanged(std::string text) {
    m_Text = text;
}
