#pragma once

#include <string>

namespace utils
{
    std::string getCurrentDir();
    const std::string readFile( const std::string& path );
}