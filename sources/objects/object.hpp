#pragma once

#include "utils/vertices/vertice.h"

#include <vector>
#include <memory>

namespace vertice
{
    class Position;
    class Normal;
    class Texture;
}

namespace object
{
    class Object
    {
    public:
        using TPosition = std::unique_ptr<vertice::Position>;
        using TNormal   = std::unique_ptr<vertice::Normal>;
        using TTexture  = std::unique_ptr<vertice::Texture>;

        std::vector<std::unique_ptr<vertice::Vertice>> vertices;

        Object( TPosition, TNormal, TTexture );
        Object(Object&&) = default;
        unsigned BlockSize() const;
        ~Object();
    };
}