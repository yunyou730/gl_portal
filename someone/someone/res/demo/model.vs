#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_pos;

uniform bool u_TestColor;

void main()
{
    v_pos = vec4(aPos,1.0);
    
    
    mat4 myModel = u_Model;
    if(u_TestColor)
    {
        myModel[0][3] += 1.0f;
    }
    
    gl_Position = v_pos * myModel * u_View * u_Projection;
}

