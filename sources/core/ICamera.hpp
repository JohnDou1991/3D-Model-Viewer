#pragma once

#include "glm.hpp"

namespace core
{
    class ICamera
    {
    public:
        virtual glm::mat4 LookAt() const = 0;
        virtual const glm::vec3& Position() const = 0;
        virtual const glm::vec3& Front() const = 0;

        virtual ~ICamera() = default;
    };
}