#include "texture.hpp"

#include "utils/image_loader.h"
#include "utils/filesystem/app_utils.hpp"

namespace core::opengl
{
    GLuint Texture::LoadImage( const utils::Image& image )
    {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

        glTexImage2D( GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data );
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::Texture(const std::string& path)
    {
        LoadImage(utils::ImageLoader().Load( path ));
    }

    void Texture::Bind(int index)
    {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_texture);
    }
}