#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 UV;

void main()
{
    gl_Position = vec4(aPos,1.0) * u_Model * u_View * u_Projection;
    UV = vec2(1.0 - aUV.x,1.0 - aUV.y);
}
