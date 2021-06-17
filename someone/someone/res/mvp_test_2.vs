#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

//uniform mat4 uMVP;

uniform mat4 uScale;
//uniform mat4 uRotateX;
//uniform mat4 uRotateY;
uniform mat4 uRotateZ;
uniform mat4 uTranslate;

//uniform mat4 uModel;
uniform mat4 uView;
//uniform mat4 uProject;

out vec3 vertColor;
out vec2 uv;

void main()
{
    vertColor = aColor;
    uv = aUV;
    
    vec4 pos = vec4(aPos,1.0);
//    pos = pos * uMVP;
    
    
    mat4 modelMatrix = uScale * uRotateZ * uTranslate;
    pos = pos * modelMatrix * uView;
    
//    gl_Position = vec4(vec3(aPos), 1.0);
    gl_Position = vec4(pos.xyz, 1.0);
}

