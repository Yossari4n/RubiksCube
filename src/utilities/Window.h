#ifndef Window_h
#define Window_h

#pragma warning(push, 0)
#include <GLFW/glfw3.h>
#pragma warning(pop)

class Window {
public:
    void Initialize(GLFWwindow* window, unsigned int width, unsigned int heigth);
    
    GLFWwindow* Pointer() const { return m_Pointer; }
    unsigned int Width() const { return m_Width; }
    unsigned int Height() const {return m_Height; }
    
    operator GLFWwindow*() { return m_Pointer; }
    
private:
    GLFWwindow* m_Pointer;
    unsigned int m_Width;
    unsigned int m_Height;
};

extern Window g_Window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
