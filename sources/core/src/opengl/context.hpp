#pragma once

#include "IContext.hpp"

#include "camera.hpp"
#include "window.hpp"

class GLFWwindow;

namespace core::opengl
{
    class Context final : public IContext
    {
        Window m_window;
        Camera m_camera;

        double m_lastTime;
        bool m_stopTime = false;

        float m_deltaTime = 0.0f;
        float m_lastFrame = 0.0f;

        void InitOpenGLContext();
        bool IsGLADOk();
        void InitOpenGL();

        // Events
        static void FrameBufferSizeCallback(GLFWwindow*, int width, int height);
        void KeyPressedCallback(int key, int scancode, int action, int mods);

    public:
        Context() noexcept;
 
        const IWindow& GetWindow() const final;
        const ICamera& GetCamera() const final;

        float FieldOfView() const final;

        double GetTime() final;
        float GetDeltaTime() final;

        void PollEvents() const final;

        ~Context();
    };
}