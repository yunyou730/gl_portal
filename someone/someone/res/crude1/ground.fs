#version 330 core

out vec4 FragColor;

uniform sampler2D u_ShadowMap;

in VS_OUT {
    vec3 FragPos;
    vec4 FragPosLightSpace;
} fs_in;


float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    float closetDepth = texture(u_ShadowMap,projCoords.xy).r;
    float currentDepth = projCoords.z;
    
    float shadow = currentDepth > closetDepth ? 1.0 : 0.0;
    return shadow;
}

void main()
{
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    
    if(shadow > 0.0)
    {
        FragColor = vec4(1.0,0.0,0.0,1.0);
    }
    else
    {
        FragColor = vec4(1.0,1.0,0.0,1.0);
    }
}

