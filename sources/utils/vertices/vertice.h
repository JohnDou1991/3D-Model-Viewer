#pragma once

#include <iostream>

namespace vertice
{
    enum EAttributeType
    {
        POSITION,
        COLOR,
        TEXTURE,
        NORMAL
    };

    class Vertice
    {
    protected:
        Vertice(float* data, unsigned length, unsigned width) : data(data), length(length), width(width)
        {

        }

    public:

        float* data;
        unsigned length;
        unsigned width;

        virtual EAttributeType GetAttributeType() const = 0;
        virtual ~Vertice() = default;
    };
}