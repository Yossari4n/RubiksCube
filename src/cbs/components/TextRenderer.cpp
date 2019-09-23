#include "TextRenderer.h"

TextRenderer::TextRenderer(const std::string& font_path, float size)
    : m_Horizontal(EAlign::NONE)
    , m_Vertical(EAlign::NONE)
    , m_Offset(0.0f)
    , m_Color(0.0f, 0.0f, 0.0f, 1.0f) {

    ImGuiIO& io = ImGui::GetIO();
    m_Font = io.Fonts->AddFontFromFileTTF(font_path.c_str(), size);
    io.Fonts->Build();
}

void TextRenderer::MakeConnectors(MessageManager& message_manager) {
    message_manager.Make(this, TextIn);
    message_manager.Make(this, ColorIn);
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

    const glm::vec2 margin = ImGui::GetWindowContentRegionMin();       // Might not be correct
    const glm::vec2 text_size = ImGui::CalcTextSize(m_Text.c_str());

    glm::vec2 pos(0.0f, 0.0f);
    pos.x = pos.x + m_Offset.x * g_Window.Width();
    pos.y = pos.y + m_Offset.y * g_Window.Height();
    IWidget::Align(&pos.x, -margin.x / 2, g_Window.Width() - margin.x / 2 - text_size.x, m_Horizontal);
    IWidget::Align(&pos.y, -margin.y / 2, g_Window.Height() - margin.y / 2 - text_size.y, m_Vertical);

    ImGui::SetWindowPos(pos);
    ImGui::TextColored(m_Color, m_Text.c_str());

    ImGui::PopFont();
    ImGui::End();
}

void TextRenderer::Font(const std::string& path, float size) {
    ImGuiIO& io = ImGui::GetIO();
    m_Font = io.Fonts->AddFontFromFileTTF(path.c_str(), size);
    io.Fonts->Build();
}

void TextRenderer::Position(glm::vec2 offset, EAlign horizontal, EAlign vertical) {
    m_Offset = offset;
    m_Vertical = vertical;
    m_Horizontal = horizontal;
}
