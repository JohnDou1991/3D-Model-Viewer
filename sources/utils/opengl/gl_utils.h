#pragma once

#include "definitions.h"

#include <string>
#include <unordered_map>

using Name = std::string;

namespace utils
{
    Shader readShader( const std::string& path, GLenum type );
    bool compileShader( Shader& shader );
    GLuint loadShaders();
}