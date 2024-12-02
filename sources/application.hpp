#pragma once

#include "utils/opengl/definitions.h"
#include <memory>

namespace core
{
    class IContext;
}

class IApplication
{
public:
    virtual void Init() = 0;
    virtual void LoadShaders() = 0;
    virtual void Start() = 0;
};

class Application : public IApplication
{
public:
    Application();
    void Init() override;
    void LoadShaders() override;
    void Start() override;
    ~Application();

private:
    struct
    {
        Shaders object;
        Shaders light;
    } m_shaders;

    std::unique_ptr<core::IContext> m_context;
};