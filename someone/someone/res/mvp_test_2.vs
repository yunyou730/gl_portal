#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 uMVP;

out vec2 uv;

void main()
{
    uv = aUV;
    vec4 pos = vec4(aPos,1.0);
    pos = pos * uMVP;
    gl_Position = pos;
}

