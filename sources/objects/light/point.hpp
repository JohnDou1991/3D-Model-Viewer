#pragma once

#include "objects/light/light.hpp"

namespace object::light
{
    class Point : public Light 
    {
        const glm::vec3& position;

    public:
        Point( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& position );

        virtual void Process(GLuint program) const override;
    };
}