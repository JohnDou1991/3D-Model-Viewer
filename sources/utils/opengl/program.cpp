#include "program.h"

#include "utils/opengl/gl_utils.h"
#include "utils/opengl/context.h"

#include <iostream>

namespace utils::opengl
{
    Program::Object::Object( Program::ObjectType type, GLuint size ) : type(type), size(size)
    {

    }

    Program::Program( Context& context ) : m_context(context)
    {

    }

    Program::~Program()
    {
        for ( auto& object : m_objects ) {
            glDeleteVertexArrays(1, &object.vao);
            glDeleteBuffers(1, &object.vbo);
            glDeleteBuffers(1, &object.ebo);
        };
        glDeleteProgram(m_shader_program);
    }

    void Program::LoadShaders( const ShaderList& shaders )
    {
        m_shader_program = utils::LoadShaders(shaders);
    }

    void Program::LoadObject( const Vertices& vertices )
    {
        m_objects.push_back( { ObjectType::ARRAY, vertices.size / 3 } );
        auto& object = m_objects.back();

        glGenVertexArrays(1, &object.vao);
        glBindVertexArray(object.vao);

        glGenBuffers(1,&object.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, object.vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size, vertices.vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0 );
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void Program::LoadObject( const Vertices& vertices, const Indices& indices )
    {
        m_objects.push_back( { ObjectType::ELEMENT, indices.size / 4 } );
        auto& object = m_objects.back();

        glGenVertexArrays(1, &object.vao);
        glBindVertexArray(object.vao);

        glGenBuffers(1,&object.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, object.vbo);

        glGenBuffers(1,&object.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.ebo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size, vertices.vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size, indices.indices, GL_STATIC_DRAW );

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0 );
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void Program::Draw()
    {
        glUseProgram(m_shader_program);
        for ( auto& object : m_objects )
        {
            glBindVertexArray(object.vao);
            switch(object.type)
            {
                case ObjectType::ARRAY:
                    glDrawArrays(GL_TRIANGLES, 0, object.size );
                    break;
                case ObjectType::ELEMENT:
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    break;
                default:
                    std::cout << "Unknown object type: " << object.type << std::endl;
                    break;
            }
            glBindVertexArray(0);
        }
    }
}