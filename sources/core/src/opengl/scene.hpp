#pragma once

#include "IScene.hpp"

#include "object.hpp"

#include <vector>

namespace core::opengl
{
    class Scene final : public IScene
    {
        std::vector<std::unique_ptr<IObject>> m_objects;
    public:

        void AddTerrain() override;
        void AddObject( std::unique_ptr<IObject> ) override;
        void AddLight() override;
        void AddCamera() override;

        void Draw() override;

        ~Scene() = default;
    };
}