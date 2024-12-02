#pragma once

#include <functional>

namespace core
{
    class IKeyboard
    {
    public:
        using OnKeyPressCallback = std::function<void(int, int, int, int)>;
        virtual void Subscribe(OnKeyPressCallback) = 0;

        virtual ~IKeyboard() = default;
    };
}