layout (location = 0) out vec4 fragColor;

struct SunLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 viewDirection;
};

struct PointLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 viewPosition;
    vec2 attenuations; // x = linearAttenuation, y = quadraticAttenuation
};

struct SpotLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 viewPosition;
    vec3 viewDirection;
    vec2 attenuations; // x = linearAttenuation, y = quadraticAttenuation
    float falloffAngle;
    float falloffExponent;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emission;
    float shininess;
};

layout (shared) uniform LightUniforms
{
    SunLight sunLights[8];
    PointLight pointLights[8];
    SpotLight spotLights[8];
};

uniform int sunLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

layout (shared) uniform MaterialUniforms
{
    Material material;
};

in vec3 normal;
in vec3 fragPos;
in vec3 color;

void main()
{
    vec3 view = normalize(fragPos);
    vec3 light = normalize(-sunLights[0].viewDirection);
    vec3 norm = normalize(normal);
    vec3 reflection = reflect(light, norm);

    vec3 ambient =  vec3(material.ambient) * sunLights[0].ambient;
    vec3 diffuse = max(dot(norm, light), 0.0f) * vec3(material.diffuse) * sunLights[0].diffuse;
    vec3 specular = pow(max(dot(reflection, view), 0.0f), material.shininess) * vec3(material.specular) * sunLights[0].specular;

    fragColor = vec4(ambient + diffuse + specular + vec3(material.emission), 1.0f);
}
