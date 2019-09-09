#ifndef Window_h
#define Window_h

#pragma warning(push, 0)
#include <GLFW/glfw3.h>

#include <string>
#pragma warning(pop)

class Window {
    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    void Initialize(unsigned int width, unsigned int heigth, const std::string& title);
    
    GLFWwindow* Pointer() const { return m_GLFWHandler; }
    unsigned int Width() const { return m_Width; }
    unsigned int Height() const {return m_Height; }
    
    operator GLFWwindow*() { return m_GLFWHandler; }
    
private:
    GLFWwindow* m_GLFWHandler{ nullptr };
    unsigned int m_Width{ 0 };
    unsigned int m_Height{ 0 };
    std::string m_Title{};
};

extern Window g_Window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
