#pragma once

#include <functional>
#include <map>
#include <vector>

struct GLFWwindow;

namespace utils::opengl::observer
{
    class Mouse
    {
        GLFWwindow* window;

        using OnMouseMoveCallback = std::function<void(GLFWwindow*, double, double)>;
        std::vector<OnMouseMoveCallback> m_subscribers;

        Mouse( GLFWwindow* );

        static void MouseMoveCallback( GLFWwindow* window, double xpos, double ypos );
        void OnMouseMove( GLFWwindow* window, double xpos, double ypos );

    public:
        static Mouse& Instance( GLFWwindow* );
        void Subscribe( OnMouseMoveCallback );
    };
}