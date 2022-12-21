#pragma once

#include "common.h"
#include "utils/opengl/definitions.h"

namespace utils::opengl
{
    class Context;

    class Program
    {
        enum ObjectType
        {
            ARRAY,
            ELEMENT
        };

        struct Object {
            Object(ObjectType, GLuint size);
            ObjectType type;

            GLuint vbo = 0;
            GLuint ebo = 0;
            GLuint vao = 0;
            GLuint size;
        };
        
        Context& m_context;
        GLuint   m_shader_program;

        std::vector<Object> m_objects;

    public:
        Program( Context& );
        ~Program();

        void LoadShaders( const ShaderList& );
        void LoadObject( const Vertices& );
        void LoadObject( const Vertices&, const Indices& );
        
        void Draw();
    };
}