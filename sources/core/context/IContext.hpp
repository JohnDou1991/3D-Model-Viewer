#pragma once

#include <memory>

namespace core
{
    class ICamera;
    class IWindow;

    class IContext
    {
    public:
        virtual const IWindow& GetWindow() const = 0;

        virtual float FieldOfView() const = 0;

        virtual double GetTime() = 0;
        virtual float GetDeltaTime() = 0;

        virtual void PollEvents() const = 0;

        virtual ~IContext() = default;
    };

    std::unique_ptr<IContext> CreateContext();
}