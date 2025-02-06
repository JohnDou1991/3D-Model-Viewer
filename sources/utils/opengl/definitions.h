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
};

using Name = std::string;
using ShaderFileName = std::string;
using Shaders = std::unordered_map<ShaderType, std::vector<ShaderFileName>>;

struct Vertices
{
    unsigned size;
    float* vertices;

    template<typename T, unsigned size>
    Vertices( T(&vertices)[size] ) : size(size*sizeof(T)), vertices(vertices)
    {

    }
};

struct Indices
{
    unsigned size;
    unsigned* indices;

    template<typename T, unsigned size>
    Indices( T(&indices)[size] ) : size(size*sizeof(T)), indices(indices)
    {

    }
};