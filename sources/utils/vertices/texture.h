#pragma once

#include "vertice.h"

namespace vertice
{
    class Texture : public Vertice
    {
    public:

        template<typename T, unsigned length>
        Texture( T(&data)[length], unsigned width ) : Vertice( data, length, width )
        {

        }

        virtual EAttributeType GetAttributeType() const override;
        ~Texture();
    };
}