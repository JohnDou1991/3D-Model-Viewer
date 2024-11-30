#pragma once

#include "utils/opengl/definitions.h"
#include "utils/opengl/program.h"

#include <memory>

namespace core
{
    class ICamera;
    class IContext;
    class IScene;
    class IShaderManager;
    class ITextureManager;
}

namespace utils
{
    class Image;
}

namespace object
{
    class Object;
    namespace light
    {
        class Light;
    }
}

class LightSource;

class IApplication
{
public:
    virtual void Init() = 0;
    virtual void LoadScene() = 0;
    virtual void Start() = 0;

    virtual ~IApplication() = default;
};

class Application : public IApplication
{
public:
    Application();

    void Init() override;
    void LoadScene() override;
    void Start() override;

    ~Application();

private:
    void LoadLightSources();
    void LoadObjects();
    void LoadShaders();

    void AddModels();
    void AddLights();
    void AddBackpack();
    void AddBoxes();

    void ComposeScene();

    void SceneTransformation(GLuint program) const;

    struct
    {
        Shaders object;
        Shaders light;
    } m_shaders;

    std::unique_ptr<core::IContext> m_context;
    std::unique_ptr<core::ICamera> m_camera;
    std::unique_ptr<core::IScene> m_scene;
    std::unique_ptr<core::IShaderManager> m_shaderManager;
    std::unique_ptr<core::ITextureManager> m_textureManager;

    using Textures = std::vector<utils::Image>;
    using Models   = std::vector<std::pair<object::Object, Textures>>;
    using Lights   = std::vector<std::unique_ptr<object::light::Light>>;

    Models m_models;
    Lights m_lights;

    utils::opengl::Program& AddProgram(const Shaders&, const Textures&);

    std::vector<LightSource> m_sources;
    std::vector<utils::opengl::Program> m_programs;
};