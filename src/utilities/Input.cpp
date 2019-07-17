#include "Input.h"

#include "Window.h"

#pragma warning(disable: 26495)
Input::Input()
    : m_AnyKeyPressed(false)
    , m_AnyKeyHold(false)
    , m_AnyKeyReleased(false)
    , m_MouseFirstMove(true)
    , m_ScrollChanged(true)
    , m_ScrollOffset(0.0f)
    , m_MousePosition(g_Window.Width() / 2.0f, g_Window.Height() / 2.0f)
    , m_MouseLastPosition(m_MousePosition)
    , m_MouseOffset(0.0f) {
    
    for (int i = 0; i < GLFW_KEY_MENU + 1; ++i) {
        m_Keys[i] = KeyState::FREE;
    }
}
#pragma warning(default: 26495)

void Input::Update(GLFWwindow *window) {
    m_AnyKeyPressed = false;
    m_AnyKeyHold = false;
    m_AnyKeyReleased = false;

    // Mouse buttons
    for (int i = 0; i < GLFW_MOUSE_BUTTON_MIDDLE; ++i) {
        if (glfwGetMouseButton(window, i) == GLFW_PRESS) {
            if (m_Keys[i] == KeyState::FREE || m_Keys[i] == KeyState::RELEASED) {
                m_Keys[i] = KeyState::PRESSED;
                m_AnyKeyPressed = true;
            }
            else if (m_Keys[i] == KeyState::PRESSED) {
                m_Keys[i] = KeyState::HOLD;
                m_AnyKeyHold = true;
            }
        }
        else {
            if (m_Keys[i] == KeyState::PRESSED || m_Keys[i] == KeyState::HOLD) {
                m_Keys[i] = KeyState::RELEASED;
                m_AnyKeyReleased = true;
            }
            else {
                m_Keys[i] = KeyState::FREE;
            }
        }
    }

    // Keyboard buttons
    for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_MENU + 1; ++i) {
        if (glfwGetKey(window, i) == GLFW_PRESS) {
            if (m_Keys[i] == KeyState::FREE || m_Keys[i] == KeyState::RELEASED) {
                m_Keys[i] = KeyState::PRESSED;
                m_AnyKeyPressed = true;
            }
            else if (m_Keys[i] == KeyState::PRESSED) {
                m_Keys[i] = KeyState::HOLD;
                m_AnyKeyHold = true;
            }

        }
        else {
            if (m_Keys[i] == KeyState::PRESSED || m_Keys[i] == KeyState::HOLD) {
                m_Keys[i] = KeyState::RELEASED;
                m_AnyKeyReleased = true;
            }
            else {
                m_Keys[i] = KeyState::FREE;
            }
        }
    }

    // Mouse position
    m_MouseOffset.x = m_MousePosition.x - m_MouseLastPosition.x;
    m_MouseOffset.y = m_MouseLastPosition.y - m_MousePosition.y;
    m_MouseLastPosition = m_MousePosition;

    // Mouse scroll
    if (!m_ScrollChanged) {
        m_ScrollOffset = 0.0f;
    }
    m_ScrollChanged = false;
}

Input::KeyState Input::GetKeyState(int glfw_key_enum) const {
    return m_Keys[glfw_key_enum];
}

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos) {
    (void*)window;

    g_Input.m_MousePosition.x = static_cast<float>(x_pos);
    g_Input.m_MousePosition.y = static_cast<float>(y_pos);
    
    // Executed only once at the beginning
    if (g_Input.m_MouseFirstMove) {
        g_Input.m_MouseLastPosition = g_Input.m_MousePosition;
        g_Input.m_MouseFirstMove = false;
    }
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    (void*)window;
    (void)x_offset;
    g_Input.m_ScrollOffset = static_cast<float>(y_offset);
    
    g_Input.m_ScrollChanged = true;
}
