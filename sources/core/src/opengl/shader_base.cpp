#include "shader_base.hpp"

#include "utils/filesystem/app_utils.hpp"
#include "utils/opengl/gl_utils.h"

#include <iostream>

namespace core::opengl
{
    ShaderBase::ShaderBase(const std::string& filename, GLenum type)
    {
        const std::string shader_file = utils::getCurrentDir() + "/resources/shaders/" + filename;

        m_shader = glCreateShader(type);

        const std::string file = utils::readFile(shader_file.c_str());
        const GLchar* source = file.c_str();

        glShaderSource(m_shader, 1, &source, NULL);
        glCompileShader(m_shader);

        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(m_shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    ShaderBase::~ShaderBase()
    {
        glDeleteShader(m_shader);
    }
}