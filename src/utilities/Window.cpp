#include "Window.h"

void Window::Initialize(unsigned int width, unsigned int height, const std::string& title) {
    m_Width = width;
    m_Height = height;
    m_Title = title;

    m_GLFWHandler = glfwCreateWindow(m_Width, m_Height, "Rubick's cube", nullptr, nullptr);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void*)window;
    g_Window.m_Width = width;
    g_Window.m_Height = height;
    glViewport(0, 0, width, height);
}
