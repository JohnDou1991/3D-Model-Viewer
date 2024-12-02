#version 330 core
out vec4 FragColor;

uniform vec4 dynamic_color;

void main()
{
    FragColor = dynamic_color;
}