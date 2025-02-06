#pragma once

#include "shader_base.hpp"

#include "common.h"

namespace core::opengl
{
    class VertexShader final : public ShaderBase
    {
    public:
        VertexShader(const std::string& filename) : ShaderBase(filename, GL_VERTEX_SHADER) {}
        ~VertexShader() = default;
    };

    class FragmentShader final : public ShaderBase
    {
    public:
        FragmentShader(const std::string& filename) : ShaderBase(filename, GL_FRAGMENT_SHADER) {}
        ~FragmentShader() = default;
    };
}