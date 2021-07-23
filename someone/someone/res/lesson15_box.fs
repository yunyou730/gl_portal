#version 330 core

uniform sampler2D u_Tex1;
uniform sampler2D u_Tex2;

in vec2 UV;
out vec4 FragColor;

void main()
{
    vec4 colorFromTexture1 = texture(u_Tex1,UV);
    vec4 colorFromTexture2 = texture(u_Tex2,UV);
    FragColor = colorFromTexture1 + colorFromTexture2;
}
