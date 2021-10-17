#version 330 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aUV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform mat4 u_LightView;
uniform mat4 u_LightProjection;

out VS_OUT {
    vec3 FragPos;
    vec4 FragPosLightSpace;
} vs_out;

void main()
{
    vec4 pos = vec4(aPos,1.0);
    gl_Position = pos * u_Model * u_View * u_Projection;
    
    vec3 worldPos = vec3(pos * u_Model);
    vs_out.FragPos = worldPos;
    vs_out.FragPosLightSpace = vec4(worldPos,1.0) * u_LightView * u_LightProjection;
}

