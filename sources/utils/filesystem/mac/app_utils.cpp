#include "utils/filesystem/app_utils.hpp"

#include <libgen.h>         // dirname
#include <mach-o/dyld.h> // _NSGetExecutablePath

#include <iostream>

namespace utils
{
    std::string getCurrentDir()
    {
        char path[PATH_MAX];

        uint32_t size = sizeof(path);
        if (_NSGetExecutablePath(path, &size) != 0)
        {
            std::cout << "buffer too small; need size " << size << std::endl;
            return {};
        }

        return dirname(path);
    }
}