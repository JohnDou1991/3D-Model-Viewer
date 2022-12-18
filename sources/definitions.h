#pragma once

#include "common.h"
#include <string>

struct Shader{
    GLuint shader;
    std::string file;
    const GLchar ** source;
};