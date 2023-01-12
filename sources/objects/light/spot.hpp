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
        Spot( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& position, const glm::vec3& direction, float cutoffIn, float cutoffOut )
            : Light(color, attenuation)
            , position(position)
            , direction(direction)
            , cutoffIn(cutoffIn)
            , cutoffOut(cutoffOut)
        {
            
        }

        virtual void Process(GLuint program) const override
        {
            Light::Process(program);

            glUniform3fv( glGetUniformLocation(program, "sLight.color.ambient"), 1, glm::value_ptr( color.ambient ) );
            glUniform3fv( glGetUniformLocation(program, "sLight.color.diffuse"), 1, glm::value_ptr( color.diffuse ) );
            glUniform3fv( glGetUniformLocation(program, "sLight.color.specular"), 1, glm::value_ptr( color.specular ) );

            glUniform1f( glGetUniformLocation(program, "sLight.attenuation.constant"), attenuation.constant );
            glUniform1f( glGetUniformLocation(program, "sLight.attenuation.linear"), attenuation.linear );
            glUniform1f( glGetUniformLocation(program, "sLight.attenuation.quadratic"), attenuation.quadratic );

            glUniform3fv( glGetUniformLocation(program, "sLight.position"), 1, glm::value_ptr( position ) );
            glUniform3fv( glGetUniformLocation(program, "sLight.direction"), 1, glm::value_ptr( direction ) );

            glUniform1f( glGetUniformLocation(program, "sLight.cutoffIn"), glm::cos(glm::radians( cutoffIn )));
            glUniform1f( glGetUniformLocation(program, "sLight.cutoffOut"), glm::cos(glm::radians( cutoffOut )));
        }
    };
}