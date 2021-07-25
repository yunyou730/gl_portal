#version 330 core

uniform sampler2D u_Tex1;

in vec2 UV;
out vec4 FragColor;


void main()
{
    vec4 texColor = texture(u_Tex1,UV);
    FragColor = texColor;
}
