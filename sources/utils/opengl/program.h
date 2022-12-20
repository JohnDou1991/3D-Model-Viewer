#pragma once

#include "common.h"
#include "utils/opengl/definitions.h"
#include "utils/opengl/init.h"

namespace utils::opengl
{
    class Program
    {
        Vertices m_vertices;
        Context m_context;

        GLuint m_vbo;
        GLuint m_vao;
        GLuint m_shader_program;

    public:
        Program( const Vertices& );

        void LoadShaders( const ShaderList& );
        void InitBuffers();
        void Draw();

        Context& context();
    };
}