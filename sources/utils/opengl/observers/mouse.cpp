#include "mouse.hpp"

#include "common.h"

#include <iostream>

namespace utils::opengl::observer
{
    void Mouse::MouseMoveCallback( GLFWwindow* window, double xpos, double ypos )
    {
        std::cout << "x: " << xpos << " y: " << ypos << std::endl;
        utils::opengl::observer::Mouse::Instance( window ).OnMouseMove( window, xpos, ypos );
    }

    Mouse::Mouse( GLFWwindow* window ) : window(window)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback( window, MouseMoveCallback );
    }

    void Mouse::OnMouseMove( GLFWwindow* window, double xpos, double ypos )
    {
        for ( auto& callback : m_subscribers )
            callback(window, xpos, ypos );
    }

    Mouse& Mouse::Instance( GLFWwindow* window )
    {
        static Mouse instance( window );
        return instance;
    }

    void Mouse::Subscribe( OnMouseMoveCallback callback )
    {
        m_subscribers.push_back(callback);
    }
}