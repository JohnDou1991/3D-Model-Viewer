#include "camera.hpp"

#include "utils/opengl/context.h"
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
}