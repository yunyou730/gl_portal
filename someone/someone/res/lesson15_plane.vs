#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 UV;

void main()
{
    vec4 pos = vec4(aPos,1.0) * u_Model * u_View * u_Projection;
    gl_Position = pos;
    
    UV = aUV;
}
