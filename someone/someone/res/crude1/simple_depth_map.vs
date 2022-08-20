#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    vec4 pos = vec4(aPos,1.0);
    gl_Position = pos * u_Model * u_View * u_Projection;
//    gl_Position.z = -1.0;
}

