#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 FragPos;
out vec3 FragNormal;

void main()
{
    gl_Position = vec4(aPos,1.0) * u_Model * u_View * u_Projection;
    
    FragNormal = aNormal * mat3(transpose(inverse(u_Model)));
    FragPos = vec3(vec4(aPos,1.0) * u_Model);
}
