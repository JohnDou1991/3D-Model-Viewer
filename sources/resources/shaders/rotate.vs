#version 330 core

layout ( location = 0 ) in vec3 pos;

uniform vec2 trigonometry;

void main()
{
    gl_Position = vec4( pos.x * trigonometry.x - pos.y * trigonometry.y
                      , pos.y * trigonometry.x + pos.x * trigonometry.y
                      , pos.z
                      , 1.0f);
}