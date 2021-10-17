#version 330 core

out vec4 FragColor;

uniform sampler2D u_ShadowMap;

in VS_OUT {
    vec3 FragPos;
    vec4 FragPosLightSpace;
} fs_in;


float ShadowCalculation(vec4 fragPosLightSpace)
{
    float bias = 0.005;

    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    
    float shadow = 0.0;
    if(projCoords.z <= 1.0)
    {
        float closetDepth = texture(u_ShadowMap,projCoords.xy).r;
        float currentDepth = projCoords.z;
        
        shadow = currentDepth - bias > closetDepth ? 1.0 : 0.0;
    }

    return shadow;
}

void main()
{
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    
    vec4 color = vec4(1.0,1.0,0.0,1.0);
    if(shadow > 0.0)
    {
        color = mix(color,vec4(1.0,0.0,0.0,1.0),0.5);
    }
    FragColor = color;
}

