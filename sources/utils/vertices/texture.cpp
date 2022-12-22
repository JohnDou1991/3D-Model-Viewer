#include "texture.h"

namespace vertice
{
    EAttributeType Texture::GetAttributeType() const
    {
        return EAttributeType::TEXTURE;
    }

    Texture::~Texture()
    {

    }
}