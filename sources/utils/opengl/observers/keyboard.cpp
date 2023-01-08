#include "keyboard.hpp"

#include "common.h"

namespace utils::opengl::observer
{
    void Keyboard::KeyPressedCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
    {
        utils::opengl::observer::Keyboard::Instance( window ).OnKeyPress( window, key, scancode, action, mods );
    }

    Keyboard::Keyboard( GLFWwindow* window ) : window(window)
    {
        glfwSetKeyCallback( window, KeyPressedCallback );
    }

    void Keyboard::OnKeyPress( GLFWwindow* window, int key, int scancode, int action, int mods )
    {
        for ( auto& callback : m_subscribers )
            callback(window, key, scancode, action, mods );
    }

    Keyboard& Keyboard::Instance( GLFWwindow* window )
    {
        static Keyboard instance( window );
        return instance;
    }

    void Keyboard::Subscribe( OnKeyPressCallback callback )
    {
        m_subscribers.push_back(callback);
    }
}