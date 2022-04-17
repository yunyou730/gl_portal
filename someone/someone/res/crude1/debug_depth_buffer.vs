#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

//uniform mat4 u_Model;
//uniform mat4 u_View;
//uniform mat4 u_Projection;

out vec2 v_UV;

void main()
{
    v_UV = aUV;
    gl_Position = vec4(aPos,1.0);
}

