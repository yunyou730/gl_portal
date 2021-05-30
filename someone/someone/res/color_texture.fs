#version 330 core

in vec3 vertColor;
in vec2 uv;

uniform sampler2D myTex;

out vec4 FragColor;

void main()
{
    vec4 colorFromVert = vec4(vertColor,1.0);
    vec4 colorFromTexture = texture(myTex,uv);
    FragColor = mix(colorFromVert,colorFromTexture,0.5);
//    FragColor = colorFromTexture;
}

