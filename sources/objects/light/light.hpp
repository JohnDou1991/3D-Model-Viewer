#pragma once

#include "glad/glad.h"
#include "glm.hpp"

#include <string>

namespace object::light
{
    class Light
    {
    public:
        struct Color {
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
        };

        struct Attenuation {
            float constant;
            float linear;
            float quadratic;
        };

    protected:
        const Color color;
        const Attenuation attenuation;

        std::string uniformName;

        Light( const Color& color, const Attenuation& attenuation );

    public:
        virtual ~Light();

        const Color& GetColor() const;
        const Attenuation& GetAttenuation() const;

        virtual void Process( GLuint program ) const = 0;
    };
};