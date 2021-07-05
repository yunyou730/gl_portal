#version 330 core

out vec4 FragColor;


struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;        // radius of specular highlight
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_ViewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 UV;

void main()
{
    // ambient
    vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse,UV));
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.position - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse,UV));
    
    // specular
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),u_Material.shininess);
    vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.specular,UV));
    
    // final color
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);
}
