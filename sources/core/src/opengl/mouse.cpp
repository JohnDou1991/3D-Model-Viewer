#include "mouse.hpp"

#include "common.h"
#include "window.hpp"

#include <iostream>

namespace core::opengl
{
    void Mouse::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
    {
        Mouse::Instance(window).OnMouseMove( window, xpos, ypos );
    }

    Mouse::Mouse(GLFWwindow* window)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, MouseMoveCallback);
    }

    void Mouse::OnMouseMove(GLFWwindow* window, double xpos, double ypos)
    {
        std::cout << "x: " << xpos << " y: " << ypos << std::endl;
        for ( auto& callback : m_subscribers )
            callback(xpos, ypos);
    }

    Mouse& Mouse::Instance(GLFWwindow* window)
    {
        static Mouse instance(window);
        return instance;
    }

    void Mouse::Subscribe(OnMouseMoveCallback callback)
    {
        m_subscribers.push_back(callback);
    }
}