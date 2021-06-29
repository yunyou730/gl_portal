#version 330 core

out vec4 FragColor;

uniform vec3 u_ObjColor;
uniform vec3 u_LightColor;

void main()
{
    FragColor = vec4(u_ObjColor * u_LightColor,1.0);
}
