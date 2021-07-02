#version 330 core

out vec4 FragColor;


struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

void main()
{
    // ambient
    vec3 ambient = u_Light.ambient * u_Material.ambient;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.position - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = u_Light.diffuse * (diff * u_Material.diffuse);
    
    // specular
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),u_Material.shininess);
    vec3 specular = u_Light.specular * spec * u_Material.specular;
    
    // final color
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);
}
