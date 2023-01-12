#pragma once

#include "objects/light/light.hpp"

namespace object::light
{
    class Point : public Light 
    {
        const glm::vec3& position;
        int m_index;

    public:
        Point( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& position )
            : Light(color, attenuation)
            , position( position )
        {
            static int index = 0;
            m_index = index++;
        }

        virtual void Process(GLuint program) const override
        {
            Light::Process(program);

            std::string indexed_name = "pLights[";
            indexed_name += std::to_string(m_index);
            indexed_name += ']';

            glUniform3fv( glGetUniformLocation(program, (indexed_name + ".color.ambient").c_str() ), 1, glm::value_ptr( color.ambient ) );
            glUniform3fv( glGetUniformLocation(program, (indexed_name + ".color.diffuse").c_str() ), 1, glm::value_ptr( color.diffuse ) );
            glUniform3fv( glGetUniformLocation(program, (indexed_name + ".color.specular").c_str() ), 1, glm::value_ptr( color.specular ) );

            glUniform1f( glGetUniformLocation(program, (indexed_name + ".attenuation.constant").c_str() ), attenuation.constant );
            glUniform1f( glGetUniformLocation(program, (indexed_name + ".attenuation.linear").c_str() ), attenuation.linear );
            glUniform1f( glGetUniformLocation(program, (indexed_name + ".attenuation.quadratic").c_str() ), attenuation.quadratic );

            glUniform3fv( glGetUniformLocation(program, (indexed_name + ".position").c_str()), 1, glm::value_ptr( position ) );
        }
    };
}