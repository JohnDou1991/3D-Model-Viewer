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
        m_objects.push_back(std::move(object));
    }

    void Scene::AddLight()
    {

    }

    void Scene::AddCamera()
    {

    }

    void Scene::Draw()
    {
        for (auto& object : m_objects)
            object->Draw();
    }
}

namespace core
{
    std::unique_ptr<IScene> CreateScene()
    {
        return std::make_unique<opengl::Scene>();
    }
}