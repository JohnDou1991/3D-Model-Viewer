#pragma once

#include "common.h"

#include "utils/opengl/definitions.h"

#include <functional>

namespace utils
{
    class Image;
}

namespace vertice
{
    class Object;
}

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

        std::vector<GLuint> m_textures;
        std::vector<Object> m_objects;

        using Transformation = std::function<void(GLuint)>;
        Transformation m_transformationFn;

        std::vector<float> GetBufferData( const vertice::Object& ) const;

    public:
        Program( Context& );
        Program( Program&& );
        ~Program();

        void LoadShaders( const ShaderList& );

        void LoadObject( const Vertices& );
        void LoadObject( const Vertices&, const Indices& );

        void LoadObject2( const Vertices& );
        void LoadObject( const vertice::Object& );
        void LoadObject( const vertice::Object&, const Indices& );

        void LoadTexture( const utils::Image& );
        void LoadTransformation( Transformation tFn );

        void Draw();
    };
}