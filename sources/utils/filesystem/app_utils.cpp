#include "utils/filesystem/app_utils.hpp"

#include <fstream>

#include "definitions.h"

namespace utils
{
    const std::string readFile( const std::string& path )
    {
        std::string result;
        std::ifstream t( path.c_str() );

        t.seekg(0, std::ios::end);   
        result.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        result.assign(( std::istreambuf_iterator<char>(t) ), std::istreambuf_iterator<char>() );
        return result;
    }
}