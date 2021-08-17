#version 330 core

in vec2 UV;
out vec4 FragColor;

uniform sampler2D u_Glyph;
uniform bool u_ByAlpha;

struct Material
{
    sampler2D diffuse;
//    sampler2D specular;
    float shininess;        // radius of specular highlight
};

void main()
{
    vec4 col = texture(u_Glyph,UV);
    
    bool test = u_ByAlpha;
//    if(u_ByAlpha)
//    {
//        if(col.a > 0.5)
//        {
//            FragColor = vec4(1.0,0.0,0.0,1.0);
//        }
//        else
//        {
//            FragColor = vec4(0.0,1.0,0.0,1.0);
//        }
//    }
//    else
//    {
        FragColor = col;
//    }
}
