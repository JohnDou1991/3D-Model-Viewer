#pragma once

#include "vertice.h"

#include <vector>
#include <memory>

namespace vertice
{
    class Object
    {
    public:
        std::vector<std::unique_ptr<Vertice>> vertices;
        unsigned block_size = 0;

    public:
        Object();
        void Add( Vertice* );

        void GenBuffers();
    };
}