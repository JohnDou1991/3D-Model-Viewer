#include "camera.hpp"

#include "GLFW/glfw3.h"

#include "utils/opengl/context.h"
#include "utils/opengl/observers/keyboard.hpp"
#include "utils/opengl/observers/mouse.hpp"

#include "utils/std/clamp.h"

namespace utils::opengl
{
    Camera::Camera( Context& context, const glm::vec3& target )
        : position( 0, 0, 3 )
        , target(target)
        , direction( glm::normalize( position - target ) )
        , right( glm::normalize( glm::cross(glm::vec3(0,1,0), direction) ))
        , up( glm::cross( direction, right ) )
        , front( glm::vec3( 0, 0, -1 ))
        , m_context(context)
    {

    }

    void Camera::Init()
    {
        utils::opengl::observer::Mouse::Instance( m_context.Window()).Subscribe(
            [this]( GLFWwindow* window, double x, double y )
            {
                if ( m_context.Window() != window )
                    return;

                float offsetX = x - mousePos.lastX;
                float offsetY = mousePos.lastY - y;

                mousePos.lastX = x;
                mousePos.lastY = y;

                const float sensitivity = 0.1f;
                offsetX *= sensitivity;
                offsetY *= sensitivity;

                eAngles.yaw += offsetX;
                eAngles.pitch += offsetY;

                eAngles.pitch = std::clamp( -89.0f, 89.0f, eAngles.pitch );

                glm::vec3 direction;
                direction.x = cos(glm::radians(eAngles.yaw)) * cos(glm::radians(eAngles.pitch));
                direction.y = sin(glm::radians(eAngles.pitch));
                direction.z = sin(glm::radians(eAngles.yaw)) * cos(glm::radians(eAngles.pitch));

                front = glm::normalize(direction);
            }
        );

        utils::opengl::observer::Keyboard::Instance( m_context.Window()).Subscribe(
            [this]( GLFWwindow* window, int key, int scancode, int action, int mods )
            {
                if ( m_context.Window() != window )
                    return;

                KeyPressedCallback( window, key, scancode, action, mods );
            }
        );
    }

    glm::mat4 Camera::LookAt() const
    {
        return glm::lookAt(
            position,
            position + front,
            up
        );
    }

    void Camera::Move( EDirection direction )
    {
        float m_cameraSpeed = SPEED * m_context.GetDeltaTime();

        switch ( direction )
        {
            case UP:
            {
                position += front * m_cameraSpeed;
                break;
            }
            case DOWN:
            {
                position -= front * m_cameraSpeed;
                break;
            }
            case LEFT:
            {
                position -= m_cameraSpeed * glm::normalize( glm::cross( front, up ) );
                break;
            }
            case RIGHT:
            {
                position += m_cameraSpeed * glm::normalize( glm::cross( front, up ) );
                break;
            }
            default:
                break;
        }
    }

    void Camera::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        switch ( key )
        {
            case GLFW_KEY_UP:
            {
                Move(Camera::EDirection::UP);
                break;
            }
            case GLFW_KEY_DOWN:
            {
                Move(Camera::EDirection::DOWN);
                break;
            }
            case GLFW_KEY_LEFT:
            {
                Move(Camera::EDirection::LEFT);
                break;
            }
            case GLFW_KEY_RIGHT:
            {
                Move(Camera::EDirection::RIGHT);
                break;
            }
            default:
                break;
        }
    }
}