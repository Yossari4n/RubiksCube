#include "Window.h"

void Window::Initialize(unsigned int width, unsigned int height, const std::string& title) {
    m_Width = width;
    m_Height = height;
    m_Title = title;

    m_GLFWHandler = glfwCreateWindow(m_Width, m_Height, "Rubick's cube", nullptr, nullptr);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void*)window;
    glViewport(0, 0, width, height);
}
