#version 330 core

out vec4 FragColor;
in vec2 UV;

uniform float u_Rows;
uniform float u_Cols;

void main()
{
    float m1 = u_Rows;
    float m2 = u_Cols;
    
    float cellWidth = 1.0 / u_Cols;
    float cellHeight = 1.0 / u_Rows;
    
    
    float col = floor(UV.x / cellWidth);
    float row = floor(UV.y / cellHeight);
    
    vec4 color1 = vec4(0.3,0.8,0.7,1.0);
    vec4 color2 = vec4(1.0,0.5,0.2,1.0);
    
    vec4 color;
    if(int(col) % 2 == 0)
    {
        if(int(row) % 2 == 0)
        {
            color = color1;
        }
        else
        {
            color = color2;
        }
    }
    else
    {
        if(int(row) % 2 == 0)
        {
            color = color2;
        }
        else
        {
            color = color1;
        }
    }
    FragColor = color;

}

