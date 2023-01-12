#pragma once

#include <string>

namespace utils
{
    struct Image
    {
        Image( const std::string& );
        Image( Image&& );
        ~Image();

        int width;
        int height;
        int nrChannels;
        int format;

        unsigned char *data;
    };

    class ImageLoader
    {
    public:
        ImageLoader();
        Image Load( const std::string& );
    };
};