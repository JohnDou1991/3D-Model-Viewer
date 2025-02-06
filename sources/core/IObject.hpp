#pragma once

namespace core
{
    class IObject
    {
    public:
        virtual void Draw() = 0;
        virtual ~IObject() = default;
    };
};