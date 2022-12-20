#pragma once

class GLFWwindow;

namespace utils::opengl
{
    class Context
    {
        GLFWwindow* m_window;

        void InitOpenGLContext();
        GLFWwindow* InitOpenGLWindow();
        bool IsGLADOk();
        void InitOpenGL();

        // Events
        static void FrameBufferSizeCallback(GLFWwindow*, int width, int height);
        static void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
        Context();
        GLFWwindow* Window() const;
    };
}