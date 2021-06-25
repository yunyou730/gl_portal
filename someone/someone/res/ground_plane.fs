#version 330 core

out vec4 FragColor;

in vec3 v_pos;

void main()
{
//    FragColor = vec4(0.5,0.62,0.25,0.5);
    
    FragColor = vec4(v_pos,1.0);
}

