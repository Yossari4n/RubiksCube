#include "TextRenderer.h"

TextRenderer::TextRenderer(const std::string& text, ImVec2 offset, EAlign horizontal, EAlign vertical)
    : m_Text(text)
    , m_Horizontal(horizontal)
    , m_Vertical(vertical) 
    , m_Offset(offset)
    , m_Color(1.0f, 1.0f, 1.0f, 1.0f) {
    assert(offset.x >= 0.0f && offset.x <= 1.0f && offset.y >= 0.0f && offset.y <= 1.0f);

    // Set font as default font
    m_Font = ImGui::GetIO().Fonts->Fonts[0];
}

void TextRenderer::Initialize() {
    Object().Scene().RegisterWidget(this);
}

void TextRenderer::Destroy() {
    Object().Scene().UnregisterWidget(this);
}

void TextRenderer::Draw() const {
    ImGui::Begin("dummy", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushFont(m_Font);

    const ImVec2 margin = ImGui::GetWindowContentRegionMin();       // Might not be correct
    const ImVec2 text_size = ImGui::CalcTextSize(m_Text.c_str());

    ImVec2 pos(0.0f, 0.0f);
    pos.x = pos.x + m_Offset.x * g_Window.Width();
    pos.y = pos.y + m_Offset.y * g_Window.Height();
    IWidget::Align(&pos.x, -margin.x / 2, g_Window.Width() - margin.x / 2 - text_size.x, m_Horizontal);
    IWidget::Align(&pos.y, -margin.y / 2, g_Window.Height() - margin.y / 2 - text_size.y, m_Vertical);

    ImGui::SetWindowPos(pos);
    ImGui::TextColored(m_Color, m_Text.c_str());

    ImGui::PopFont();
    ImGui::End();
}

void TextRenderer::ChangeFont(std::string path, float size) {
    ImGuiIO& io = ImGui::GetIO();
    m_Font = io.Fonts->AddFontFromFileTTF(path.c_str(), size);
    io.Fonts->Build();
}

void TextRenderer::ChangeText(std::string text) {
    m_Text = text;
}


void TextRenderer::ChangeColor(ImVec4 color) {
    m_Color = color;
}
