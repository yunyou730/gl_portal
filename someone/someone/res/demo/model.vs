#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_pos;

void main()
{
    v_pos = vec4(aPos,1.0);
    gl_Position = v_pos * u_Model * u_View * u_Projection;
}

