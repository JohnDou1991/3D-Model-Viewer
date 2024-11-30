#pragma once

#include "utils/opengl/definitions.h"

namespace utils
{
    Shader ReadShader( const std::string& path, GLenum type );
    bool CompileShader( const Shader& shader );
    GLuint LoadShaders( const Shaders& );
}