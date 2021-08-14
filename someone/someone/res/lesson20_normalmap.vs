#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 FragNormal;
out vec2 UV;

out VS_OUT
{
    vec3 FragPos;
    vec2 TexCoord;
    mat3 TBN;
} vs_out;

void main()
{
    gl_Position = vec4(aPos,1.0) * u_Model * u_View * u_Projection;
    
    mat3 normalMatrix = mat3(transpose(inverse(u_Model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 B = normalize(normalMatrix * aBitangent);
    vec3 N = normalize(normalMatrix * aNormal);
    mat3 TBN = transpose(mat3(T,B,N));
    
    FragNormal = aNormal * mat3(transpose(inverse(u_Model)));
    vs_out.FragPos = vec3(vec4(aPos,1.0) * u_Model);
    vs_out.TexCoord = aUV;
    vs_out.TBN = TBN;
    
    UV = aUV;
}
