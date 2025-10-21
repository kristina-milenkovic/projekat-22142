//#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCords;

out vec2 TexCords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model*vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCords = aTexCords;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}

//#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 dirLightDirection;
uniform vec3 dirLightColor;

uniform vec3 viewPos;
uniform float shininess;
uniform vec3 ambientStrength;
uniform vec3 specularColor;

uniform vec3 spotLightPos;
uniform vec3 spotLightDir;
uniform vec3 spotLightColor;
uniform float spotCutOff;
uniform float spotOuterCutOff;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 texColor = texture(texture_diffuse1, TexCords).rgb;

    // DIRECTIONAL
    vec3 lightDir = normalize(-dirLightDirection);

    // Ambient
    vec3 ambient = ambientStrength * dirLightColor;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * dirLightColor;

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularColor * spec;

    vec3 result = (ambient + diffuse + specular) * texColor;

    // SPOTLIGHT
    vec3 spotDir = normalize(spotLightPos - FragPos);
    float theta = dot(spotDir, normalize(-spotLightDir));

    float epsilon = spotCutOff - spotOuterCutOff;
    float intensity = clamp((theta - spotOuterCutOff) / epsilon, 0.0, 1.0);

    // Diffuse spotlight
    float diffSpot = max(dot(norm, spotDir), 0.0);
    vec3 diffuseSpot = diffSpot * spotLightColor;

    // Specular spotlight
    vec3 reflectDirSpot = reflect(-spotDir, norm);
    float specSpot = pow(max(dot(viewDir, reflectDirSpot), 0.0), shininess);
    vec3 specularSpot = specularColor * specSpot;

    vec3 spotEffect = (diffuseSpot + specularSpot) * intensity;


    vec3 finalColor = result + spotEffect * texColor;
    FragColor = vec4(finalColor, 1.0);
}