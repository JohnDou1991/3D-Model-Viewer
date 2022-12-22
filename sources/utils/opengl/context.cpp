#include "context.h"

#include "common.h"
#include "config.h"
#include "DisplaySettings.h"

#include <iostream>

namespace utils::opengl
{
    void Context::InitOpenGLContext()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // this is for MacOS
    }

    GLFWwindow* Context::InitOpenGLWindow()
    {
        GLFWwindow* window = glfwCreateWindow(
            DisplaySettings::Window(DisplaySettings::CurrentMode).width()
          , DisplaySettings::Window(DisplaySettings::CurrentMode).height()
          , "LearnOpenGL"
          , NULL
          , NULL
        );

        if (!window)
        {
            std::cout << "Failed to create GLFW window..." << std::endl;
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(window);
        return window;
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

    void Context::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        #ifdef DEBUG_KEYBOARD_EVENTS
            std::cout << "key: " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods << std::endl;
        #endif

        if ( action != GLFW_PRESS )
            return;

        switch(key)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window,1);
                break;
            }
            case GLFW_KEY_F:
            {
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                break;
            }
            case GLFW_KEY_L:
            {
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                break;
            }
            default:
                break;
        }
    }

    void Context::InitOpenGL()
    {
        InitOpenGLContext();

        m_window = InitOpenGLWindow();
        if(!m_window)
            return;

        if(!IsGLADOk())
            return;

        FrameBufferSizeCallback(
            nullptr
          , DisplaySettings::Window(DisplaySettings::CurrentMode).width()
          , DisplaySettings::Window(DisplaySettings::CurrentMode).height() 
        );

        glfwSetFramebufferSizeCallback( m_window, FrameBufferSizeCallback );
        glfwSetKeyCallback( m_window, KeyPressedCallback );

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    Context::Context() : m_window(nullptr)
    {
        InitOpenGL();

        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    }

    GLFWwindow* Context::Window() const
    {
        return m_window;
    }
}