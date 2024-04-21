#pragma once

#include "ITexture.hpp"

#include <memory>
#include <string>

namespace core
{
    class ITextureManager
    {
    public:
        virtual std::weak_ptr<ITexture> LoadTexture(const std::string& filename) = 0;

        virtual ~ITextureManager() = default;
    };

    std::unique_ptr<ITextureManager> CreateTextureManager();
}