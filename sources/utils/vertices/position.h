#pragma once

#include "vertice.h"

namespace vertice
{
    class Position : public Vertice
    {
    public:

        template<typename T, unsigned length>
        Position( T(&data)[length], unsigned width ) : Vertice( data, length, width )
        {

        }

        virtual EAttributeType GetAttributeType() const override;
        ~Position();
    };
}