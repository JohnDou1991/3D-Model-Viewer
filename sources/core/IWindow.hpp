#pragma once

#include "IKeyboard.hpp"
#include "IMouse.hpp"

#include "DisplaySettings.h"

namespace core
{
    class IWindow
    {
    public:
        virtual int Height() const = 0;
        virtual int Width() const = 0;
        virtual float AspectRatio() const = 0;

        virtual bool ShouldClose() const = 0;
        virtual void SwapBuffers() const = 0;

        virtual IKeyboard& GetKeyboard() const = 0;
        virtual IMouse& GetMouse() const = 0;

        virtual void SetWindowSize(DisplaySettings::Window) = 0;

        ~IWindow() = default;
    };
}