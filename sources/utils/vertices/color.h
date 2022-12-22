#pragma once

#include "vertice.h"

namespace vertice
{
    class Color : public Vertice
    {
    public:

        template<typename T, unsigned length>
        Color( T(&data)[length], unsigned width ) : Vertice( data, length, width )
        {

        }

        virtual EAttributeType GetAttributeType() const override;
        ~Color();
    };
}