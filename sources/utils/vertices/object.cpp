#include "object.h"

namespace vertice
{
    Object::Object()
    {

    }

    void Object::Add( Vertice* v )
    {
        block_size += v->width;
        vertices.emplace_back(v);
    }

    void Object::GenBuffers()
    {
        // for ( auto& vertice : vertices )

    }
}