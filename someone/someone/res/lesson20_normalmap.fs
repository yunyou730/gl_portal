#version 330 core

in vec3 FragNormal;
in vec2 UV;

in VS_OUT
{
    vec3 FragPos;
    vec2 TexCoord;
    mat3 TBN;
} fs_in;

out vec4 FragColor;

uniform sampler2D u_NormalMap;
uniform vec3 u_CameraPos;
uniform bool u_EnableNormalMap;
uniform bool u_EnableWrongNormalMap;

struct Material
{
    sampler2D diffuse;
//    sampler2D specular;
    float shininess;        // radius of specular highlight
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


uniform Material    u_Material;
uniform PointLight  u_PointLight;

vec3 phongPointLight(PointLight light,vec3 normalDir,vec3 camPos,Material material)
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,UV));
    
    // diffuse
    vec3 norm = normalize(normalDir);
    vec3 lightDir = -normalize(fs_in.FragPos - light.position);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,UV));
    
    // specular
    vec3 viewDir = normalize(camPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
//    vec3 specular = light.specular * spec * vec3(texture(material.specular,UV));
    vec3 specular = light.specular * spec;      // temp as no specular map
    
    // attenuation
    float dis = length(light.position - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * dis * dis);
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ambient + diffuse + specular;
}

vec3 getNormalByNormalMap()
{
    // [0,1]
    vec3 curNormal = texture(u_NormalMap,UV).rgb;
    // [0,1] -> [-1,1]
    curNormal = normalize(curNormal * 2.0 - 1.0);
    
    // 错误的 不经过 tbn 变换 的
    if(u_EnableWrongNormalMap)
    {
        return curNormal;
    }
    // apply TBN, convert normal from TBN coordinate ,to world coordinate
    curNormal = normalize(fs_in.TBN * curNormal);
    return curNormal;
}

void main()
{
    vec2 t = fs_in.TexCoord;
    
    vec3 curNormal = getNormalByNormalMap();
    if(!u_EnableNormalMap)
    {
        curNormal = FragNormal;
    }
    
    vec3 colorByPointLight = phongPointLight(u_PointLight,curNormal,u_CameraPos,u_Material);
    FragColor = vec4(colorByPointLight,1.0);//vec4(color,1.0);
    
}
