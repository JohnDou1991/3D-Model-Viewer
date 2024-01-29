#include "window.hpp"

#include "common.h"
#include "keyboard.hpp"
#include "mouse.hpp"

#include <iostream>

namespace core::opengl
{
    void Window::Init()
    {
        DisplaySettings::Window windowSettings(DisplaySettings::Mode::HD);

        GLFWwindow* window = glfwCreateWindow(
            windowSettings.width()
          , windowSettings.height()
          , "LearnOpenGL"
          , glfwGetPrimaryMonitor()
          , NULL
        );

        if (!window)
        {
            std::cout << "Failed to create GLFW window..." << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        m_window = window;

        if ( m_window )
        {
            m_keyboard = &Keyboard::Instance(m_window);
            m_mouse = &Mouse::Instance(m_window);
        }
        else
            throw("Failed to init window");
    }

    Window::Window() 
        : m_window(nullptr)
        , m_keyboard(nullptr)
        , m_mouse(nullptr)
    {

    }

    int Window::Height() const
    {
        int width, height;
        glfwGetWindowSize( m_window, &width, &height );
        return height;
    }

    int Window::Width() const
    {
        int width, height;
        glfwGetWindowSize( m_window, &width, &height );
        return width;
    }

    float Window::AspectRatio() const
    {
        int width, height;
        glfwGetWindowSize( m_window, &width, &height );
        return width/(float)height;
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(m_window);
    }

    IKeyboard& Window::GetKeyboard() const
    {
        return *m_keyboard;
    }

    IMouse& Window::GetMouse() const
    {
        return *m_mouse;
    }

    void Window::SetWindowSize(DisplaySettings::Window window)
    {
        glfwSetWindowSize(m_window, window.width(), window.height());
    }
}