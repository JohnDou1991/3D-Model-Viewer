#pragma once

namespace vertices
{
    float triangle1[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
    };

    float triangle2[] = {
        0.0f,  0.0f, 0.0f,
        0.5f,  0.0f, 0.0f,
        0.25f, 0.5f, 0.0f,
    };

    float triangle3[] = {
        0.5f,   0.5f,  0.0f,
        0.75f,  0.5f,  0.0f,
        0.625f, 0.75f, 0.0f,
    };

    float triangle4[] = {
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
    };

    float rectangle1[] = {
        // first triangle
        0.5f,  0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
       -0.5f,  0.5f, 0.0f, // top left
        // second triangle
        0.5f, -0.5f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f  // top left
    };

    float rectangle2[] = {
        0.75f,  0.75f, 0.0f, // top right
        0.75f, -0.75f, 0.0f, // bottom right
       -0.75f, -0.75f, 0.0f, // bottom left
       -0.75f,  0.75f, 0.0f  // top left
    };

    unsigned indices1[] = { // note that we start from 0!
       0, 1, 3, // first triangle
       1, 2, 3  // second triangle
    };

    float color1[] = {
        1.0f, 0.0f, 0.0f, // bottom right
        0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.0f, 1.0f, // top
        1.0f, 1.0f, 0.0f
    };

    float texCoords1[] = {
        1.0f, 0.0f, // lower-right corner
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-center corner
        0.0f, 0.0f, // lower-left corner
    };

    float texCoords2[] = {
        0.75f, 0.25f, // lower-right corner
        0.75f, 0.75f, // top-right
        0.25f, 0.75f, // top-center corner
        0.25f, 0.25f, // lower-left corner
    };

    float cube1[] = {
       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
       -0.5f,  0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,

       -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,
       
       -0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       
       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f, -0.5f,
       
       -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f, -0.5f,
   };

   float cube1_tex_coords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
   };
}