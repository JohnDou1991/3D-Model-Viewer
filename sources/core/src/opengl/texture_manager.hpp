#pragma once

#include "ITextureManager.hpp"

#include <map>

namespace core::opengl
{
    class TextureManager final : public ITextureManager
    {
        std::map<std::string, std::shared_ptr<ITexture>> m_textures;

    public:
        virtual std::weak_ptr<ITexture> LoadTexture(const std::string& filename) override;

        ~TextureManager() = default;
    };
}