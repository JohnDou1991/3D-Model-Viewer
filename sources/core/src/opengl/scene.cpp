#include "scene.hpp"

#include <memory>

namespace core::opengl
{
    void Scene::AddTerrain()
    {
        // todo
    }

    void Scene::AddObject( std::unique_ptr<IObject> object )
    {

    }

    void Scene::AddLight()
    {

    }

    void Scene::AddCamera()
    {

    }

    void Scene::Draw()
    {

    }
}

namespace core
{
    std::unique_ptr<IScene> CreateScene()
    {
        return std::make_unique<opengl::Scene>();
    }
}