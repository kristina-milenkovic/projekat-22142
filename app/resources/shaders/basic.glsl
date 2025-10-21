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

void main()
{

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-dirLightDirection);


    vec3 ambient = ambientStrength * dirLightColor;


    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * dirLightColor;


    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularColor * spec;

    vec3 texColor = texture(texture_diffuse1, TexCords).rgb;


    vec3 result = (ambient + diffuse + specular) * texColor;

    FragColor = vec4(result, 1.0);
}
