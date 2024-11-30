#pragma once

#include <functional>
#include <memory>

struct GLFWwindow;

namespace core
{
    class IKeyboard
    {
    public:
        using OnKeyPressCallback = std::function<void(int, int, int, int)>;
        virtual void Subscribe(OnKeyPressCallback) = 0;

        virtual ~IKeyboard() = default;
    };

    IKeyboard& CreateKeyboardHandler(GLFWwindow*);
}