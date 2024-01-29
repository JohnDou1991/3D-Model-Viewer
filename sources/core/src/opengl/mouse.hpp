#pragma once

#include "IMouse.hpp"

#include <vector>

struct GLFWwindow;

namespace core::opengl
{
    class Mouse final : public IMouse
    {
        using OnMouseMoveCallback = std::function<void(double, double)>;
        std::vector<OnMouseMoveCallback> m_subscribers;

        Mouse(GLFWwindow*);

        static void MouseMoveCallback( GLFWwindow* window, double xpos, double ypos );
        void OnMouseMove( GLFWwindow* window, double xpos, double ypos );

    public:

        static Mouse& Instance(GLFWwindow*);
        void Subscribe(OnMouseMoveCallback) final;

        ~Mouse() = default;
    };
}