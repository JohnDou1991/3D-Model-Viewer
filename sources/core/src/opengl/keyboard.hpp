#pragma once

#include "IKeyboard.hpp"

#include <vector>

struct GLFWwindow;

namespace core::opengl
{
    class Keyboard final : public IKeyboard
    {
        std::vector<OnKeyPressCallback> m_subscribers;

        Keyboard(GLFWwindow*);

        static void KeyPressedCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
        void OnKeyPress( GLFWwindow* window, int key, int scancode, int action, int mods );

    public:

        static Keyboard& Instance(GLFWwindow*);
        void Subscribe(OnKeyPressCallback) final;

        ~Keyboard() = default;
    };
}