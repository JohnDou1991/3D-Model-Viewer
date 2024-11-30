#include "utils/opengl/gl_utils.h"
#include "utils/filesystem/app_utils.hpp"

#include <iostream>
#include <vector>

GLuint shaderProgram;

namespace utils
{
    Shader ReadShader( const std::string& path, GLenum type )
    {
        Shader result;
        GLuint shader = glCreateShader(type);
        result.shader = shader;
        result.file = readFile( path );
        return result;
    }

    bool CompileShader( const Shader& shader )
    {
        const GLchar* source = shader.file.c_str();
        glShaderSource(shader.shader, 1, &source, NULL);
        glCompileShader(shader.shader);

        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(shader.shader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(shader.shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << "info: " << infoLog << std::endl;
        }

        return success;
    }

    GLuint LoadShaders( const Shaders& list )
    {
        std::string dir = utils::getCurrentDir() + "/resources/shaders/";
        std::vector<Shader> shaders;

        for ( const auto& pair : list )
            for ( const auto& filename : pair.second )
            {
                shaders.emplace_back( ReadShader( (dir + filename).c_str(), pair.first ) );
                CompileShader( shaders.back() );
            }

        shaderProgram = glCreateProgram();

        for ( auto& shader : shaders )
            glAttachShader(shaderProgram, shader.shader);

        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        for ( auto& shader : shaders )
            glDeleteShader(shader.shader);

        return shaderProgram;
    }
} // namespace utils