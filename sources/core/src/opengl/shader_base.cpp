#include "shader_base.hpp"

#include "utils/filesystem/app_utils.hpp"
#include "utils/opengl/gl_utils.h"

#include <iostream>

namespace core::opengl
{
    ShaderBase::ShaderBase(const std::string& filename, GLenum type)
    {
        const auto shader = utils::ReadShader(filename, type);
        if (utils::CompileShader(shader))
        {
            m_shader = shader.shader;
        }
    }

    ShaderBase::~ShaderBase()
    {
        glDeleteShader(m_shader);
    }
}