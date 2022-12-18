#include "utils/filesystem/app_utils.hpp"

#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX

#include <iostream>

namespace utils
{
    std::string getCurrentDir()
    {
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        const char *path;
        if (count != -1) {
            path = dirname(result);
        }
        return path;
    }
}