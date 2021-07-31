#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_TextureDir;

void main()
{
    
    mat4 tm = u_Model;
    mat4 tempView = mat4(
                         u_View[0][0],u_View[0][1],u_View[0][2],0.0,
                         u_View[1][0],u_View[1][1],u_View[1][2],0.0,
                         u_View[2][0],u_View[2][1],u_View[2][2],0.0,
                         0.0,0.0,0.0,1.0);
//    vec4 pos = vec4(aPos,1.0) * u_Model * u_View * u_Projection;
    vec4 pos = vec4(aPos,1.0) * tempView * u_Projection;
    
    gl_Position = pos;
    
    v_TextureDir = normalize(aPos);
}
