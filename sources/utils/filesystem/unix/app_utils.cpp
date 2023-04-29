#include "utils/filesystem/app_utils.hpp"

#include <libgen.h>         // dirname
#include <unistd.h>         // readlink

#include <linux/limits.h> // linux PATH_MAX

#include <iostream>

namespace utils
{
    std::string getCurrentDir()
    {
        char path[PATH_MAX];

        ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
        if (count < 0) 
        {
            std::cout << "Failed to get current dir: " << count << std::endl;
            return {};
        }

        return dirname(path);
    }
}