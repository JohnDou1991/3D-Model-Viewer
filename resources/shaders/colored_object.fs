#version 330 core

in vec3 buffer_color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(buffer_color, 1.0f);
}