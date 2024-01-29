#include "object.hpp"

#include "utils/vertices/normal.h"
#include "utils/vertices/position.h"
#include "utils/vertices/texture.h"

#include <numeric>

namespace object
{
    Object::Object(TPosition position, TNormal normal, TTexture texture)
    {
        vertices.emplace_back(position.release());
        vertices.emplace_back(normal.release());
        vertices.emplace_back(texture.release());
    }

    unsigned Object::BlockSize() const
    {
        return std::accumulate(vertices.begin(), vertices.end(), 0,
            []( const unsigned result, const std::unique_ptr<vertice::Vertice>& vertices )
            {
                return result + vertices->width;
            });
    }

    Object::~Object()
    {

    }
}