#include "light.hpp"

#include "glm/gtc/type_ptr.hpp"

namespace object::light
{
    Light::Light( const Color& color, const Attenuation& attenuation ) : color(color), attenuation(attenuation)
    {

    }

    Light::~Light()
    {

    }

    const Light::Color& Light::GetColor() const
    {
        return color;
    }

    const Light::Attenuation& Light::GetAttenuation() const
    {
        return attenuation;
    }

    void Light::Process( GLuint program ) const
    {
        glUniform3fv( glGetUniformLocation(program, (uniformName + ".color.ambient").c_str() ), 1, glm::value_ptr( color.ambient ) );
        glUniform3fv( glGetUniformLocation(program, (uniformName + ".color.diffuse").c_str() ), 1, glm::value_ptr( color.diffuse ) );
        glUniform3fv( glGetUniformLocation(program, (uniformName + ".color.specular").c_str() ), 1, glm::value_ptr( color.specular ) );

        glUniform1f( glGetUniformLocation(program, (uniformName + ".attenuation.constant").c_str() ), attenuation.constant );
        glUniform1f( glGetUniformLocation(program, (uniformName + ".attenuation.linear").c_str() ), attenuation.linear );
        glUniform1f( glGetUniformLocation(program, (uniformName + ".attenuation.quadratic").c_str() ), attenuation.quadratic );
    }
}