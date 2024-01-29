#pragma once

#include <functional>

namespace core
{
    class IMouse
    {
    public:
        using OnMouseMoveCallback = std::function<void(double, double)>;
        virtual void Subscribe(OnMouseMoveCallback) = 0;

        virtual ~IMouse() = default;
    };
}