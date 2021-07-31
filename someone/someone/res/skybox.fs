#version 330 core

out vec4 FragColor;
in vec3 v_Pos;

in vec3 v_TextureDir;
uniform samplerCube u_CubeMap;

void main()
{
    FragColor = texture(u_CubeMap,v_TextureDir);
}
