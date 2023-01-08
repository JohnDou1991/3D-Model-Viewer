#include "program.h"

#include "utils/opengl/gl_utils.h"
#include "utils/opengl/context.h"
#include "utils/image_loader.h"

#include "utils/vertices/object.h"

#include <iostream>
#include <cmath>

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

    void Program::LoadObject2( const Vertices& vertices )
    {
        m_objects.push_back( { ObjectType::ARRAY, vertices.size / 3 } );
        auto& object = m_objects.back();

        glGenVertexArrays(1, &object.vao);
        glBindVertexArray(object.vao);

        glGenBuffers(1,&object.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, object.vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size, vertices.vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0 );
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(float)) );

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    std::vector<float> Program::GetBufferData( const vertice::Object& object ) const
    {
        std::vector<float> result;
        size_t vertex_count = object.vertices.front()->length / object.vertices.front()->width;
        for ( size_t i = 0; i < vertex_count; ++i )
            for ( size_t j = 0; j < object.vertices.size(); ++j )
                for ( unsigned k = 0 + object.vertices[j]->width * i, end = 0 + object.vertices[j]->width * (i+1); k < end; ++k )
                    result.push_back( object.vertices[j]->data[k] );
        return result;
    }

    void Program::LoadObject( const vertice::Object& object )
    {
        m_objects.push_back( { ObjectType::ARRAY, object.vertices.front()->length / object.vertices.front()->width } );
        auto& obj = m_objects.back();

        glGenVertexArrays(1, &obj.vao);
        glBindVertexArray(obj.vao);

        glGenBuffers(1,&obj.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);

        std::vector<float> data = GetBufferData(object);

        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

        unsigned offset = 0;
        for ( size_t i = 0; i < object.vertices.size(); ++i )
        {
            auto& vertice = object.vertices[i];

            glVertexAttribPointer(i, vertice->width, GL_FLOAT, GL_FALSE, object.block_size * sizeof(GLfloat), (GLvoid*)(offset*sizeof(GLfloat)));
            glEnableVertexAttribArray(i);
            offset += vertice->width;
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Program::LoadObject( const vertice::Object& object, const Indices& indices )
    {
        m_objects.push_back( { ObjectType::ELEMENT, indices.size / 4 } );
        auto& obj = m_objects.back();

        glGenVertexArrays(1, &obj.vao);
        glBindVertexArray(obj.vao);

        glGenBuffers(1,&obj.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);

        glGenBuffers(1,&obj.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ebo);

        std::vector<float> data = GetBufferData(object);

        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size, indices.indices, GL_STATIC_DRAW );

        unsigned offset = 0;
        for ( size_t i = 0; i < object.vertices.size(); ++i )
        {
            auto& vertice = object.vertices[i];

            glVertexAttribPointer(i, vertice->width, GL_FLOAT, GL_FALSE, object.block_size * sizeof(GLfloat), (GLvoid*)(offset*sizeof(GLfloat)));
            glEnableVertexAttribArray(i);
            offset += vertice->width;
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Program::LoadTexture( const utils::Image& image )
    {
        m_textures.emplace_back(0);
        glGenTextures(1, &m_textures.back());
        glBindTexture(GL_TEXTURE_2D, m_textures.back());

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data );
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Program::Draw()
    {
        glUseProgram(m_shader_program);

        std::vector<const char*> textures = {"texture1", "texture2"};

        for ( size_t i = 0; i < textures.size(); ++i )
            glUniform1i(glGetUniformLocation(m_shader_program, textures[i]), i);

        m_transformationFn(m_shader_program);

        for ( auto& object : m_objects )
        {
            for ( size_t i = 0; i < m_textures.size(); ++i ) 
            {
                glActiveTexture(GL_TEXTURE0+i);
                glBindTexture(GL_TEXTURE_2D, m_textures[i]);
            }
            glBindVertexArray(object.vao);

            switch(object.type)
            {
                case ObjectType::ARRAY:
                    glDrawArrays(GL_TRIANGLES, 0, object.size );
                    break;
                case ObjectType::ELEMENT:
                    glDrawElements(GL_TRIANGLES, object.size, GL_UNSIGNED_INT, 0);
                    break;
                default:
                    std::cout << "Unknown object type: " << object.type << std::endl;
                    break;
            }
            glBindVertexArray(0);
        }
    }
}