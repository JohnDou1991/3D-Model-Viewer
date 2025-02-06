#pragma once

namespace core
{
    class ITexture
    {
    public:
        virtual void Bind(int index) = 0;
        virtual ~ITexture() = default;
    };
} // namespace core
