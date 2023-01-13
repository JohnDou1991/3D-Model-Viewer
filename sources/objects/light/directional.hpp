#pragma once

#include "objects/light/light.hpp"

namespace object::light
{
    class Directional : public Light 
    {
        const glm::vec3 direction;

    public:
        Directional( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& direction );

        virtual void Process(GLuint program) const override;
    };
}