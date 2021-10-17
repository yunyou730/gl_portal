#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aOffset;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform mat4 u_ScaleMat;

void main()
{
    vec4 modelPos = vec4(aPos,1.0);
    mat4 modelMatrix = u_ScaleMat * u_Model;
    vec4 pos = modelPos * modelMatrix + vec4(aOffset,0.0);
    
    pos = pos * u_View * u_Projection;
    gl_Position = pos;
}

