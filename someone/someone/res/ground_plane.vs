#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uMVP;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_pos;

void main()
{
    v_pos = vec3(aPos.x,aPos.y,0.3);
    
    vec4 pos = vec4(aPos,1.0);
    pos = pos * u_Model * u_View * u_Projection;
    gl_Position = pos;
}

