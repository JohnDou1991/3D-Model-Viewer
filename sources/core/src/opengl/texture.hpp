#pragma once

#include "common.h"

#include "ITexture.hpp"

#include <string>

namespace utils
{
    class Image;
}

namespace core::opengl
{
    class Texture final : public ITexture
    {
        GLuint m_texture;

        GLuint LoadImage( const utils::Image& );
    public:
        Texture(const std::string& path);
        void Bind(int index) override;
        ~Texture();
    };
}