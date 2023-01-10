#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture1;

float specularStrength = 0.95;

void main() 
{
    // ambient light
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize( lightPos - FragPos );

    float diff = max( dot(norm, lightDir), 0.0 );
    vec3 diffuse = diff * lightColor;

    // specular light
    vec3 viewDir = normalize( viewPos - FragPos );
    vec3 reflectDir = reflect( -lightDir, norm );

    float spec = pow(max(dot(viewDir,reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // use vertex color
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4( result, 1.0 );

    // use texture color
    // vec3 result = (ambient + diffuse + specular) * texture(texture1, TexCoord).xyz;
    // FragColor = vec4( result, 1.0 );
}
