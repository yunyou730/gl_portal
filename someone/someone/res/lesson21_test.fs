#version 330 core

in vec2 UV;
out vec4 FragColor;

uniform sampler2D u_Glyph;

void main()
{
    vec4 col = texture(u_Glyph,UV);
    
    
    FragColor = vec4(1.0,1.0,1.0,col.r);
}
