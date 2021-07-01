#version 330 core

out vec4 FragColor;

uniform vec3 u_ObjColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // ambient
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * u_LightColor;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_LightPos - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * u_LightColor;
    
    // specular
    float specularStrength = 0.6;
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = specularStrength * spec * u_LightColor;
    
    // result
    vec3 result = (ambient + diffuse + specular) * u_ObjColor;
    FragColor = vec4(result,1.0);
}
