#include "spot.hpp"

#include "glm/gtc/type_ptr.hpp"

namespace object::light
{
    Spot::Spot( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& position, const glm::vec3& direction, float cutoffIn, float cutoffOut )
        : Light(color, attenuation)
        , position(position)
        , direction(direction)
        , cutoffIn(cutoffIn)
        , cutoffOut(cutoffOut)
    {
        uniformName = "sLight";
    }

    void Spot::Process(GLuint program) const
    {
        Light::Process(program);

        glUniform3fv( glGetUniformLocation(program, (uniformName + ".position").c_str()), 1, glm::value_ptr( position ) );
        glUniform3fv( glGetUniformLocation(program, (uniformName + ".direction").c_str()), 1, glm::value_ptr( direction ) );

        glUniform1f( glGetUniformLocation(program, (uniformName + ".cutoffIn").c_str()), glm::cos(glm::radians( cutoffIn )));
        glUniform1f( glGetUniformLocation(program, (uniformName +".cutoffOut").c_str()), glm::cos(glm::radians( cutoffOut )));
    }
}