#pragma once

#include "IObject.hpp"

#include <vector>

namespace core
{
    class IShader;
    class ITexture;
    class IShaderManager;
    class ITextureManager;
}

namespace assets
{
    class Cube final : public core::IObject
    {
        std::vector<std::weak_ptr<core::IShader>> m_shaders;
        std::vector<std::weak_ptr<core::ITexture>> m_textures;
    public:
        Cube(const std::unique_ptr<core::IShaderManager>&
            , const std::unique_ptr<core::ITextureManager>&
        );

        void Draw() override;

        ~Cube();
    };
}