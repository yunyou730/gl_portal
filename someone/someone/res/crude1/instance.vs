#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

uniform vec2 u_offsets[100];

out vec3 col;

void main()
{
    vec2 offset = u_offsets[gl_InstanceID];
    gl_Position = vec4(aPos + aOffset,0.0,1.0);
    col = aColor;
}

