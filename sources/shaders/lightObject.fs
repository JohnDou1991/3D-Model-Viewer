#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 viewPos;

uniform sampler2D texture1;
uniform sampler2D texture2;

struct Color {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    Color color;
    float shininess;
};
uniform Material material;

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;
    Color color;
    Attenuation attenuation;
};
uniform DirectionalLight dLight;

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutoffIn;
    float cutoffOut;

    Color color;
    Attenuation attenuation;
};
uniform SpotLight sLight;

#define MAX_LIGHT_SOURCES 16
struct PointLight {
    vec3 position;
    Color color;
    Attenuation attenuation;
};
uniform PointLight pLights[MAX_LIGHT_SOURCES];
uniform int pLightsCount = 4;

vec3 AmbientLight(vec3 ambient)
{
    vec3 result = ambient * vec3(texture(texture1, TexCoord));
    return result;
}

vec3 DiffuseLight( vec3 lightDir, Color color )
{
    float diff = max( dot(normalize(Normal), lightDir), 0.0 );
    vec3 diffuse = color.diffuse * (diff * vec3(texture(texture1, TexCoord)));

    return diffuse;
}

vec3 SpecularLight( vec3 lightDir, Color color )
{
    vec3 viewDir = normalize( viewPos - FragPos );
    vec3 reflectDir = reflect( -lightDir, normalize(Normal) );

    float spec = pow(max(dot(viewDir,reflectDir), 0.0), material.shininess);
    vec3 specular = sLight.color.specular * ( spec * vec3(texture(texture2, TexCoord)) );

    return specular;
}

float AttenuationLight(vec3 position, Attenuation attenuation)
{
    float distance = length( position - FragPos );
    float result = 1.0 / (attenuation.constant + attenuation.linear * distance + attenuation.quadratic * (distance * distance));
    return result;
}

vec3 SLight()
{
    vec3 ambient  = AmbientLight(sLight.color.ambient);
    vec3 lightDir = normalize( sLight.position - FragPos );

    vec3 diffuse  = DiffuseLight(lightDir, sLight.color);
    vec3 specular = SpecularLight(lightDir, sLight.color);

    vec3 result;

    { // attenuation

        float attenuation = AttenuationLight( sLight.position, sLight.attenuation );

        float theta = dot( lightDir, normalize(-sLight.direction) );
        float epsilon = sLight.cutoffIn - sLight.cutoffOut;
        float intensity = clamp( (theta - sLight.cutoffIn) / epsilon , 0.0f, 1.0f );

        diffuse *= intensity;
        specular *= intensity;

        if ( theta > sLight.cutoffIn )
            result = ambient + diffuse + specular;
        else
            result = ambient;

        result *= attenuation;
    }

    return result;
}

vec3 DLight()
{
    vec3 ambient = AmbientLight(dLight.color.ambient);
    vec3 lightDir = normalize( dLight.direction );

    vec3 diffuse = DiffuseLight(lightDir, dLight.color);
    vec3 specular = SpecularLight(lightDir, dLight.color);

    return ambient + diffuse + specular;
}

vec3 PLight(int i)
{
    PointLight pLight = pLights[i];

    vec3 ambient = AmbientLight(pLight.color.ambient);
    vec3 lightDir = normalize( pLight.position - FragPos );

    vec3 diffuse = DiffuseLight(lightDir, pLight.color);
    vec3 specular = SpecularLight(lightDir, pLight.color);

    vec3 result = ambient + diffuse + specular;

    { // attenuation
        float attenuation = AttenuationLight( pLight.position, pLight.attenuation );
        result *= attenuation;
    }

    return result;
}

void main() 
{
    vec3 result = SLight() + DLight();
    for ( int i = 0; i < pLightsCount && i < MAX_LIGHT_SOURCES; ++i )
        result += PLight(i);
    FragColor = vec4( result, 1.0 );
}
