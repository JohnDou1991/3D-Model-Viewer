#include "context.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "utils/std/clamp.h"

#include "IKeyboard.hpp"

#include "DisplaySettings.h"

#include <iostream>

namespace core::opengl
{
    void Context::InitOpenGLContext()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // this is for MacOS
        #endif
    }

    bool Context::IsGLADOk()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD..." << std::endl;
            return false;
        }
        return true;
    }

    void Context::FrameBufferSizeCallback(GLFWwindow*, int width, int height)
    {
        glViewport( 0, 0, width, height );
    }

    void Context::KeyPressedCallback(int key, int scancode, int action, int mods)
    {
        #ifdef DEBUG_KEYBOARD_EVENTS
            std::cout << "key: " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods << std::endl;
        #endif

        if ( action != GLFW_PRESS )
            return;

        switch(key)
        {
            case GLFW_KEY_EQUAL:
            {
                m_window.SetWindowSize(DisplaySettings::Window(DisplaySettings::Mode::HD));
                break;
            }
            case GLFW_KEY_MINUS:
            {
                m_window.SetWindowSize(DisplaySettings::Window(DisplaySettings::Mode::SD));
                break;
            }
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(m_window.m_window,1);
                break;
            }
            case GLFW_KEY_F:
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            }
            case GLFW_KEY_L:
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            }
            case GLFW_KEY_SPACE:
            {
                m_stopTime = !m_stopTime;
                break;
            }
            default:
                break;
        }
    }

    void Context::InitOpenGL()
    {
        InitOpenGLContext();

        m_window.Init();
        if(!m_window.m_window)
            return;

        if(!IsGLADOk())
            return;

        FrameBufferSizeCallback(
            nullptr
          , m_window.Width()
          , m_window.Height()
        );

        glfwSetFramebufferSizeCallback( m_window.m_window, FrameBufferSizeCallback );

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    Context::Context() noexcept
        :  m_lastFrame(glfwGetTime())
    {
        InitOpenGL();

        m_window.GetKeyboard().Subscribe(
            [this](int key, int scancode, int action, int mods)
            {
                KeyPressedCallback(key, scancode, action, mods);
            }
        );

        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

        #ifdef DEBUG_LOGGING
            std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
        #endif

        glEnable(GL_DEPTH_TEST);
    }

    const IWindow& Context::GetWindow() const
    {
        return m_window;
    }

    float Context::FieldOfView() const
    {
        return 45.0f;
    }

    double Context::GetTime()
    {
        if (!m_stopTime)
            return m_lastTime = glfwGetTime();
        return m_lastTime;
    }

    float Context::GetDeltaTime()
    {
        float currentTime = glfwGetTime();
        m_deltaTime = currentTime - m_lastFrame;
        m_lastFrame = currentTime;

        return std::clamp<float>( 0, 0.1, m_deltaTime );
    }

    void Context::PollEvents() const
    {
        glfwPollEvents();
    }

    Context::~Context()
    {
        glfwTerminate();
    }
}

namespace core
{
    std::unique_ptr<IContext> CreateContext()
    {
        return std::make_unique<opengl::Context>();
    }
}