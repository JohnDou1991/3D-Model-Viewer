#pragma once

#include <functional>
#include <memory>

struct GLFWwindow;

namespace core
{
    class IMouse
    {
    public:
        using OnMouseMoveCallback = std::function<void(double, double)>;
        virtual void Subscribe(OnMouseMoveCallback) = 0;

        virtual ~IMouse() = default;
    };

    IMouse& CreateMouseHandler(GLFWwindow*);
}