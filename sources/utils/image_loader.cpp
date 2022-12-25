#include "image_loader.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace utils
{
    Image::Image( const std::string& path ) : data(nullptr)
    {
        data = stbi_load( path.c_str(), &width, &height, &nrChannels, 0);
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