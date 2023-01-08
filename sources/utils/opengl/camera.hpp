#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

namespace utils::opengl
{
    class Context;

    class Camera
    {
        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 direction;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 front;

        Context& m_context;

        const float SPEED = 0.5f;

        struct
        {
            float lastX = 400;
            float lastY = 300;
        } mousePos;

        struct
        {
            float yaw = -90;
            float pitch = 0;
        } eAngles;

    public:
        Camera( Context&, const glm::vec3& target = glm::vec3( 0,0,0 ) );

        void Init();

        glm::mat4 LookAt() const;

        enum EDirection {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        void Move(EDirection);
    };
}