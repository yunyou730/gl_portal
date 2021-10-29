#version 330 core

out vec4 FragColor;

in vec3 v_TextureDir;

void main()
{
//    FragColor = vec4(0.2,1.0,0.2,1.0);
    FragColor = vec4(v_TextureDir,1.0);
}
