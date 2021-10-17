#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aOffset;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    vec4 pos = vec4(aPos + aOffset,1.0) * u_Model * u_View * u_Projection;
    gl_Position = pos;
//    gl_Position = vec4(aPos,1.0);
}

