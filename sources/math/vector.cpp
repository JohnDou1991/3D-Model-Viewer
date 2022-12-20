#include "math/vector.h"

namespace math
{
    vector::vector( float x, float y, float z ) : x(x), y(y), z(z)
    {

    }

    float vector::dot( const vector& rhs )
    {
        float result = 0;

        result += this->x * rhs.x;
        result += this->y * rhs.y;
        result += this->z * rhs.z;

        return result;
    }

    vector vector::cross( const vector& rhs )
    {
        vector result(
            (this->y * rhs.z) - (this->z * rhs.y)
           ,(this->z * rhs.x) - (this->x * rhs.z)
           ,(this->x * rhs.y) - (this->y * rhs.x)
        );
        return result;
    }
}