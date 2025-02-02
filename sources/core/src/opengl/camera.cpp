#include "camera.hpp"

#include "GLFW/glfw3.h"

#include "IContext.hpp"
#include "ICamera.hpp"
#include "IWindow.hpp"

#include "utils/std/clamp.h"

namespace core::opengl
{
    Camera::Camera( IContext& context, const glm::vec3& target )
        : position( 0, 0, 8 )
        , target(target)
        , direction( glm::normalize( position - target ) )
        , right( glm::normalize( glm::cross(glm::vec3(0,1,0), direction) ))
        , up( glm::cross( direction, right ) )
        , front( glm::vec3( 0, 0, -1 ))
        , m_context(context)
    {
        Init();
    }

    void Camera::Init()
    {
        mousePos.lastX = m_context.GetWindow().Width() / 2;
        mousePos.lastY = m_context.GetWindow().Height() / 2;

        m_context.GetWindow().GetMouse().Subscribe(
            [this]( double x, double y )
            {
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

        m_context.GetWindow().GetKeyboard().Subscribe(
            [this](int key, int scancode, int action, int mods )
            {

                KeyPressedCallback(key, scancode, action, mods);
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

    const glm::vec3& Camera::Position() const
    {
        return position;
    }

    const glm::vec3& Camera::Front() const
    {
        return front;
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

    void Camera::KeyPressedCallback(int key, int scancode, int action, int mods)
    {
        if ( action == GLFW_RELEASE )
            return;

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

namespace core
{
    std::unique_ptr<ICamera> CreateCamera(IContext& context)
    {
        return std::make_unique<opengl::Camera>(context);
    }
}