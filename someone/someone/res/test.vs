#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertColor;
void main()
{
    vertColor = aColor;
    gl_Position = vec4(vec3(aPos), 1.0);
}

