#version 330 core


struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    
    sampler2D texture_diffuse2;
    sampler2D texture_specular2;
    
    float shininess;
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

uniform Material material;

uniform DirectionLight u_DirectionLight;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;
uniform vec3 u_ViewPos;

uniform bool u_bEnableDirLight;
uniform bool u_bEnablePointLight;
uniform bool u_bEnableSpotLight;

in vec2 uv;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


vec3 calcPhongColor(vec3 lightAmbientCol,
                    vec3 lightDiffuseCol,
                    vec3 lightSpecularCol)
{
    vec3 result;
    return result;
}

vec3 calcColorByDirLight(DirectionLight light,
                         vec3 matAmbientCol,
                         vec3 matDiffuseCol,
                         vec3 matSpecularCol,float matShininess)
{
    vec3 ambientCol = light.ambient * matAmbientCol;
    
    vec3 norm = normalize(Normal);
    vec3 minusLightDir = -normalize(light.direction);
    float diff = max(dot(norm,minusLightDir),0.0);
    vec3 diffuseCol = light.diffuse * diff * matDiffuseCol;
    
    
    vec3 reflectDir = reflect(normalize(light.direction),norm);
    vec3 viewLookDir = normalize(u_ViewPos - FragPos);
    float spec = max(dot(viewLookDir,reflectDir),0.0);
    spec = pow(spec,matShininess);
    vec3 specularCol = light.specular * spec * matSpecularCol;
    
    return ambientCol + diffuseCol + specularCol;
}

vec3 calcColorByPointLight(PointLight light,
                           vec3 matAmbientCol,
                           vec3 matDiffuseCol,
                           vec3 matSpecularCol,float matShininess)
{
    vec3 ambientCol = light.ambient * matAmbientCol;
    
    vec3 norm = normalize(Normal);
    vec3 minusLightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm,minusLightDir),0.0);
    vec3 diffuseCol = light.diffuse * diff * matDiffuseCol;

    
    vec3 reflectDir = reflect(normalize(FragPos - light.position),norm);
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),matShininess);
    vec3 specularCol = light.specular * spec * matSpecularCol;
    
    float dis = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * dis * dis);
    
    ambientCol *= attenuation;
    diffuseCol *= attenuation;
    specularCol *= attenuation;
    
    return ambientCol + diffuseCol + specularCol;
}

vec3 calcColorBySpotLight(SpotLight light,
                            vec3 matAmbientCol,
                            vec3 matDiffuseCol,
                            vec3 matSpecularCol,float matShininess)
{
    vec3 result = vec3(0.0);
    
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir,normalize(-light.direction));
    
    vec3 ambientCol = light.ambient * matAmbientCol;
    
    if(theta >= light.outerCutOff)
    {
        // intensity
        float intensity = 1.0;
        float epsilon = light.cutOff - light.outerCutOff;
        intensity = clamp((theta - light.outerCutOff) / epsilon,0.0,1.0);
        
        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm,normalize(light.position - FragPos)),0.0);
        vec3 diffuseCol = light.diffuse * diff * matDiffuseCol;
        
        // specular
        vec3 viewDir = normalize(u_ViewPos - FragPos);
        vec3 reflectDir = reflect(normalize(FragPos - light.position),norm);
        float spec = pow(max(dot(viewDir,reflectDir),0.0),matShininess);
        vec3 specular = light.specular * spec * matSpecularCol;
        
        result = ambientCol + (diffuseCol) * intensity;
    }
    else
    {
        result = ambientCol;
    }
    
    return result;
}

void main()
{
    vec4 colorDiffuse = texture(material.texture_diffuse1,uv);
    vec4 colorSpecular = texture(material.texture_specular1,uv);
    
    vec3 colByDirLight = vec3(0.0);
    vec3 colByPointLight = vec3(0.0);
    vec3 colBySpotLight = vec3(0.0);
    
    if(u_bEnableDirLight)
    {
        colByDirLight = calcColorByDirLight(u_DirectionLight,
                                       vec3(colorDiffuse),
                                       vec3(colorDiffuse),
                                       vec3(colorSpecular),
                                       material.shininess);
    }

    if(u_bEnablePointLight)
    {
        colByPointLight = calcColorByPointLight(u_PointLight,
                                                     vec3(colorDiffuse),
                                                     vec3(colorDiffuse),
                                                     vec3(colorSpecular),
                                                     material.shininess);
    }

    if(u_bEnableSpotLight)
    {
        colBySpotLight = calcColorBySpotLight(u_SpotLight,
                                                     vec3(colorDiffuse),
                                                     vec3(colorDiffuse),
                                                     vec3(colorSpecular),
                                                     material.shininess);
    }
    
    
    FragColor = vec4(colByDirLight + colByPointLight + colBySpotLight,1.0);
}

