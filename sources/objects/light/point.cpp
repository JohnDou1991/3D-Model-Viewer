#include "point.hpp"

#include "glm/gtc/type_ptr.hpp"

namespace object::light
{
    Point::Point( const Light::Color& color, const Light::Attenuation& attenuation, const glm::vec3& position )
        : Light(color, attenuation)
        , position( position )
    {
        static int index = 0;

        std::string indexed_name = "pLights[";
        indexed_name += std::to_string(index++);
        indexed_name += ']';

        uniformName = indexed_name;
    }

    void Point::Process(GLuint program) const
    {
        Light::Process(program);

        glUniform3fv( glGetUniformLocation(program, (uniformName + ".position").c_str()), 1, glm::value_ptr( position ) );
    }
}