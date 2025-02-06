#pragma once

#include "IShader.hpp"

#include "common.h"

#include <string>

namespace core::opengl
{
    class ShaderBase : public IShader
    {
        GLuint m_shader;
    protected:
        ShaderBase(const std::string& filename, GLenum type);
        ~ShaderBase();
    };
}