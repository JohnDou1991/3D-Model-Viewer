#pragma once

#include "IObject.hpp"

class Shader;
class Texture;
class Vertices;

namespace core::opengl
{
    class Object : public IObject
    {
    public:
        Object(Shader&, Texture&, Vertices&);
        ~Object() = default;
    };
}