#pragma once

#include "glm.hpp"

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

        Light( const Color& color, const Attenuation& attenuation ) : color(color), attenuation(attenuation)
        {

        }

    public:
        virtual ~Light()
        {

        }

        const Color& GetColor() const
        {
            return color;
        }

        const Attenuation& GetAttenuation() const
        {
            return attenuation;
        }

        virtual void Process( GLuint program ) const
        {
            // TODO
            // glUniform3fv( glGetUniformLocation(program, "light.ambient"), 1, glm::value_ptr( color.ambient ) );
            // glUniform3fv( glGetUniformLocation(program, "light.diffuse"), 1, glm::value_ptr( color.diffuse ) );
            // glUniform3fv( glGetUniformLocation(program, "light.specular"), 1, glm::value_ptr( color.specular ) );

            // glUniform1f( glGetUniformLocation(program, "light.constant"), attenuation.constant );
            // glUniform1f( glGetUniformLocation(program, "light.linear"), attenuation.linear );
            // glUniform1f( glGetUniformLocation(program, "light.quadratic"), attenuation.quadratic );
        }
    };
};