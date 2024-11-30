#pragma once

#include "IWindow.hpp"

class GLFWwindow;

class IKeyboard;
class IMouse;

namespace core::opengl
{
    class Window final : public IWindow
    {
        IKeyboard* m_keyboard;
        IMouse* m_mouse;
    public:
        GLFWwindow* m_window;
        Window();

        void Init();

        int Height() const final;
        int Width() const final;
        float AspectRatio() const final;

        bool ShouldClose() const final;
        void SwapBuffers() const final;

        IKeyboard& GetKeyboard() const final;
        IMouse& GetMouse() const final;

        void SetWindowSize(DisplaySettings::Window) final;

        ~Window() = default;
    };
}