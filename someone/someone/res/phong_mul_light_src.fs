#version 330 core

out vec4 FragColor;


struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;        // radius of specular highlight
};

struct DirectionLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform DirectionLight u_DirLight;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;

uniform bool u_bEnableDirLight;
uniform bool u_bEnablePointLight;
uniform bool u_bEnableSpotLight;

in vec3 Normal;
in vec3 FragPos;
in vec2 UV;

vec3 CalcWithDirectionLight(DirectionLight light)
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse,UV));
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = -normalize(light.direction);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse,UV));
    
    // specular
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),u_Material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular,UV));
    
    return ambient + diffuse + specular;
}

vec3 CalcWithPointLight(PointLight light)
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse,UV));
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = -normalize(FragPos - light.position);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse,UV));
    
    // specular
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),u_Material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular,UV));
    
    // attenuation
    float dis = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * dis * dis);
//    float attenuation = 1.0;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
//    return ambient + diffuse + specular;
    // @miao @temp
    return specular;
}

vec3 CalcWithSpotLight(SpotLight light)
{
    vec3 lightDir = -normalize(FragPos - light.position);
    
    vec3 result = vec3(0.0,0.0,0.0);
    
    // ambient
    vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse,UV));
    
        
    // cutOff
    float thetaCos = dot(lightDir,normalize(-light.direction));
    
    if(thetaCos > light.outerCutOff)
    {
        float intensity = 1.0;
        float epsilon = light.cutOff - light.outerCutOff;
        intensity = clamp((thetaCos - light.outerCutOff) / epsilon,0.0,1.0);
       
        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm,lightDir),0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse,UV));
        
        // specular
        vec3 viewDir = normalize(u_ViewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir,norm);
        float spec = pow(max(dot(viewDir,reflectDir),0.0),u_Material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(u_Material.specular,UV));
        
        result = ambient + (diffuse + specular) * intensity;
    }
    else
    {
        result = ambient;
    }
    return result;
}

void main()
{
    vec3 dirLightColor = vec3(0.0);
    if(u_bEnableDirLight)
    {
        dirLightColor = CalcWithDirectionLight(u_DirLight);
    }
        
    vec3 pointLightColor = vec3(0.0);
    if(u_bEnablePointLight)
    {
        pointLightColor = CalcWithPointLight(u_PointLight);
    }

    
    vec3 spotLightColor = vec3(0.0);
    if(u_bEnableSpotLight)
    {
        spotLightColor = CalcWithSpotLight(u_SpotLight);
    }

    
    vec3 result = dirLightColor + pointLightColor + spotLightColor;
    FragColor = vec4(result,1.0);
}
