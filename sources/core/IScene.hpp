#pragma once

#include "IObject.hpp"

#include <memory>

namespace core
{
    class IScene
    {
    public:
        virtual void AddTerrain() = 0;
        virtual void AddObject( std::unique_ptr<IObject> ) = 0;
        virtual void AddLight() = 0;
        virtual void AddCamera() = 0;

        virtual void Draw() = 0;

        virtual ~IScene() = default;
    };

    std::unique_ptr<IScene> CreateScene();
}