#include "image_loader.h"

#include "glad/glad.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace utils
{
    Image::Image( const std::string& path ) : data(nullptr)
    {
        data = stbi_load( path.c_str(), &width, &height, &nrChannels, 0);
        switch ( nrChannels )
        {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = -1;
                break;
        }
    }

    Image::Image( Image&& rhs )
        : width(rhs.width)
        , height(rhs.height)
        , nrChannels(rhs.nrChannels)
        , format(rhs.format)
    {
        data = rhs.data;
        rhs.data = nullptr;
    }

    Image::~Image()
    {
        if (data)
            stbi_image_free(data);
    }

    ImageLoader::ImageLoader()
    {

    }

    Image ImageLoader::Load( const std::string& path )
    {
        return Image(path);
    }
};