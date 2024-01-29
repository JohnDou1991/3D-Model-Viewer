#include "directional.hpp"

#include "gtc/type_ptr.hpp"

namespace object::light
{
    Directional::Directional( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& direction )
        : Light(color, attenuation)
        , direction(direction)
    {
        uniformName = "dLight";
    }

    void Directional::Process(GLuint program) const
    {
        Light::Process(program);

        glUniform3fv( glGetUniformLocation(program, (uniformName + ".direction").c_str()), 1, glm::value_ptr( direction ) );
    }
}