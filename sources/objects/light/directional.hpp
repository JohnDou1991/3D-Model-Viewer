#pragma once

#include "objects/light/light.hpp"

namespace object::light
{
    class Directional : public Light 
    {
        const glm::vec3 direction;

    public:
        Directional( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& direction )
            : Light(color, attenuation)
            , direction(direction)
        {

        }

        virtual void Process(GLuint program) const override
        {
            Light::Process(program);

            glUniform3fv( glGetUniformLocation(program, "dLight.color.ambient"), 1, glm::value_ptr( color.ambient ) );
            glUniform3fv( glGetUniformLocation(program, "dLight.color.diffuse"), 1, glm::value_ptr( color.diffuse ) );
            glUniform3fv( glGetUniformLocation(program, "dLight.color.specular"), 1, glm::value_ptr( color.specular ) );

            glUniform1f( glGetUniformLocation(program, "dLight.attenuation.constant"), attenuation.constant );
            glUniform1f( glGetUniformLocation(program, "dLight.attenuation.linear"), attenuation.linear );
            glUniform1f( glGetUniformLocation(program, "dLight.attenuation.quadratic"), attenuation.quadratic );

            glUniform3fv( glGetUniformLocation(program, "dLight.direction"), 1, glm::value_ptr( direction ) );
        }
    };
}