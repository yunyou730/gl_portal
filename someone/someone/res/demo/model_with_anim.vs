#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aBoneIds;
layout (location = 2) in vec4 aBoneWeights;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform mat4 u_BoneTransforms[50];  // all bones transforms

void main()
{
    vec4 boneWeights = normalize(aBoneWeights);
    
    mat4 boneTransform = mat4(0.0);
    boneTransform += u_BoneTransforms[int(aBoneIds.x)] * boneWeights.x;
    boneTransform += u_BoneTransforms[int(aBoneIds.y)] * boneWeights.y;
    boneTransform += u_BoneTransforms[int(aBoneIds.z)] * boneWeights.z;
    boneTransform += u_BoneTransforms[int(aBoneIds.w)] * boneWeights.w;
    
    vec4 pos = boneTransform * vec4(aPos,1.0);
    gl_Position = pos * u_Model * u_View * u_Projection;
}
