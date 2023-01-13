#pragma once

#include "objects/light/light.hpp"

#include <iostream>

namespace object::light
{
    class Spot : public Light 
    {
        const glm::vec3& position;
        const glm::vec3& direction;

        const float cutoffIn = 0;
        const float cutoffOut = 0;

    public:
        Spot( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& position, const glm::vec3& direction, float cutoffIn, float cutoffOut );

        virtual void Process(GLuint program) const override;
    };
}