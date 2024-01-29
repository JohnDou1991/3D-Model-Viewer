#pragma once

#include "ICamera.hpp"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

namespace core::opengl
{
    class Context;

    class Camera final : public ICamera
    {
        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 direction;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 front;

        Context& m_context;

        const float SPEED = 1.0f;

        struct
        {
            float lastX;
            float lastY;
        } mousePos;

        struct
        {
            float yaw = -90;
            float pitch = 0;
        } eAngles;

        enum EDirection {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        void KeyPressedCallback(int key, int scancode, int action, int mods);
        void Move(EDirection);

    public:
        Camera( Context&, const glm::vec3& target = glm::vec3( 0,0,0 ) );

        void Init();

        glm::mat4 LookAt() const final;
        const glm::vec3& Position() const final;
        const glm::vec3& Front() const final;

        ~Camera() = default;
    };
}