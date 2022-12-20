#include "program.h"

#include "utils/opengl/gl_utils.h"

namespace utils::opengl
{
    Program::Program( const Vertices& vertices ) : m_vertices(vertices), m_context()
    {

    }

    void Program::LoadShaders( const ShaderList& shaders )
    {
        m_shader_program = utils::LoadShaders(shaders);
    }

    void Program::InitBuffers( )
    {
        glGenBuffers(1,&m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glBufferData(GL_ARRAY_BUFFER, m_vertices.size, m_vertices.vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void Program::Draw()
    {
        glUseProgram(m_shader_program);
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size/3);
        glBindVertexArray(0);
    }

    Context& Program::context()
    {
        return m_context;
    }
}