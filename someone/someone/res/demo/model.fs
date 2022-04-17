#version 330 core

out vec4 FragColor;

in vec4 v_pos;

void main()
{
    vec3 col = vec3(fract(v_pos.y));
    FragColor = vec4(col,1.0);
}
