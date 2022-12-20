#pragma once

namespace math
{
    class vector
    {
    public:
        const float x, y, z;
    public:
        vector( float x, float y, float z);

        // operations
        float dot(const vector& rhs);
        vector cross(const vector& rhs);
    };
}