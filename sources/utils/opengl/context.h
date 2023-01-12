#pragma once

#include "utils/opengl/camera.hpp"

class GLFWwindow;

namespace utils::opengl
{
    class Context
    {
        GLFWwindow* m_window;
        Camera m_camera;

        float m_deltaTime = 0.0f;
        float m_lastFrame = 0.0f;

        void InitOpenGLContext();
        GLFWwindow* InitOpenGLWindow();
        bool IsGLADOk();
        void InitOpenGL();

        // Events
        static void FrameBufferSizeCallback(GLFWwindow*, int width, int height);
        void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
        Context();

        GLFWwindow* Window() const;
        const Camera& GetCamera() const;

        int WindowHeight() const;
        int WindowWidth() const;
        float AspectRatio() const;
        float FieldOfView() const;

        float GetDeltaTime();
    };
}