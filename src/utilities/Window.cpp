#include "Window.h"

void Window::Initialize(GLFWwindow* window, unsigned int width, unsigned int height) {
    m_Pointer = window;
    m_Width = width;
    m_Height = height;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void*)window;
    glViewport(0, 0, width, height);
}
