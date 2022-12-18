#include "utils/opengl/gl_utils.h"
#include "utils/filesystem/app_utils.hpp"

#include <iostream>

GLuint shaderProgram;
std::unordered_map<Name,Shader> shaderPool;

namespace utils
{
    Shader readShader( const std::string& path, GLenum type )
    {
        Shader result;
        GLuint shader = glCreateShader(type);
        result.shader = shader;
        result.file = readFile( path );
        return result;
    }

    bool compileShader( Shader& shader )
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
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return success;
    }

    GLuint loadShaders()
    {
        std::string current_dir = utils::getCurrentDir();

        shaderPool["vertex"] = std::move(readShader( (current_dir + "/resources/shaders/vertex_shader").c_str(), GL_VERTEX_SHADER ));
        if ( !compileShader(shaderPool["vertex"]) ) return 0;

        shaderPool["fragment"] = readShader( (current_dir + "/resources/shaders/fragment_shader").c_str(), GL_FRAGMENT_SHADER );
        if ( !compileShader(shaderPool["fragment"]) ) return 0;

        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, shaderPool["vertex"].shader);
        glAttachShader(shaderProgram, shaderPool["fragment"].shader);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        glDeleteShader(shaderPool["vertex"].shader);
        glDeleteShader(shaderPool["fragment"].shader);

        std::cout << "Shaders loaded..." << std::endl;

        return shaderProgram;
    }
} // namespace utils