#pragma once

#include <string>

namespace utils
{
    struct Image
    {
        Image( const std::string& );
        ~Image();

        int width;
        int height;
        int nrChannels;

        unsigned char *data;
    };

    class ImageLoader
    {
    public:
        ImageLoader();
        Image Load( const std::string& );
    };
};