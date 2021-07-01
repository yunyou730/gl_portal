#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 Normal;
out vec3 FragPos;

void main()
{
//    Normal = aNormal;
    Normal = aNormal * mat3(transpose(inverse(u_Model)));
    FragPos = vec3(vec4(aPos,1.0) * u_Model);
    
    vec4 pos = vec4(aPos,1.0) * u_Model * u_View * u_Projection;
    gl_Position = pos;
}
