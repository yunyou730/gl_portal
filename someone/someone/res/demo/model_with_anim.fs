#version 330 core

out vec4 FragColor;

void main()
{
    vec3 col = vec3(1.0,1.0,0.3);
    FragColor = vec4(col,1.0);
}
