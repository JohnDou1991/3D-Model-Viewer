#pragma once

#include <functional>
#include <map>
#include <vector>

struct GLFWwindow;

namespace utils::opengl::observer
{
    class Keyboard
    {
        GLFWwindow* window;

        using OnKeyPressCallback = std::function<void(GLFWwindow*, int, int, int, int)>;
        std::vector<OnKeyPressCallback> m_subscribers;

        Keyboard( GLFWwindow* );

        static void KeyPressedCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
        void OnKeyPress( GLFWwindow* window, int key, int scancode, int action, int mods );

    public:

        static Keyboard& Instance( GLFWwindow* );
        void Subscribe( OnKeyPressCallback );
    };
}