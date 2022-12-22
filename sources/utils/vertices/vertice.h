#pragma once

namespace vertice
{
    enum EAttributeType
    {
        POSITION,
        COLOR,
        TEXTURE
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