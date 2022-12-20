#pragma once

#include "common.h"

#include <string>
#include <vector>
#include <unordered_map>

enum ShaderType
{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

struct Shader{
    GLuint shader;
    std::string file;
    const GLchar ** source;
};

using Name = std::string;
using ShaderFileName = std::string;
using ShaderList = std::unordered_map<ShaderType, std::vector<ShaderFileName>>;

struct Vertices
{
    unsigned size;
    float* vertices;

    template<typename T, unsigned size>
    Vertices( T(&vertices)[size] ) : size(size*sizeof(T)), vertices(vertices)
    {

    }
}; 