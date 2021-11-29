#version 330 core

out vec4 FragColor;

in vec4 v_pos;
uniform bool u_TestColor;

void main()
{
//    FragColor = vec4(0.2,1.0,0.2,1.0);
//    FragColor = vec4(v_TextureDir,1.0);
    vec3 col = vec3(fract(v_pos.y));
    if(u_TestColor)
    {
        col = vec3(1.0,1.0,0.3);
    }
    FragColor = vec4(col,1.0);
}
