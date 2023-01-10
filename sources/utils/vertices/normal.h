#pragma once

#include "vertice.h"

namespace vertice
{
    class Normal : public Vertice
    {
    public:

        template<typename T, unsigned length>
        Normal( T(&data)[length], unsigned width ) : Vertice( data, length, width )
        {

        }

        virtual EAttributeType GetAttributeType() const override;
        ~Normal();
    };
}