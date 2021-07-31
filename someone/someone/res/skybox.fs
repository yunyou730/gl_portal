#version 330 core

out vec4 FragColor;
in vec3 v_Pos;

in vec3 v_TextureDir;
uniform samplerCube u_CubeMap;


/*
 x+  red
 x-  yello
 
 y+  green
 y-  strange green blue
 
 
 z+ blue
 z- pink
 


int GetFaceIndex()
{
    float absX = abs(v_TextureDir.x);
    float absY = abs(v_TextureDir.y);
    float absZ = abs(v_TextureDir.z);
    
    if(absX >= absY && absX >= absZ)
    {
        return v_TextureDir.x > 0.0 ? 0 : 1;
    }
    if(absY >= absX && absY >= absZ)
    {
        return v_TextureDir.y > 0.0 ? 2 : 3;
    }
    if(absZ >= absX && absZ >= absY)
    {
        return v_TextureDir.z > 0.0 ? 4 : 5;
    }
    
    return 0;
}
*/

void main()
{
//    int faceIdx = GetFaceIndex();
    vec4 texCol = texture(u_CubeMap,v_TextureDir);
    FragColor = texCol;
//
//    vec4 col = vec4(1.0);
//    if(faceIdx == 0)
//    {
//        col = vec4(1.0,0.0,0.0,1.0);
//    }
//    else if(faceIdx == 1)
//    {
//        col = vec4(1.0,1.0,0.0,1.0);
//    }
//    else if(faceIdx == 2)
//    {
//        col = vec4(0.0,1.0,0.0,1.0);
//    }
//    else if(faceIdx == 3)
//    {
//        col = vec4(0.0,1.0,1.0,1.0);
//    }
//    else if(faceIdx == 4)
//    {
//        col = vec4(0.0,0.0,1.0,1.0);
//    }
//    else if(faceIdx == 5)
//    {
//        col = vec4(1.0,0.0,1.0,1.0);
//    }
//
//    FragColor = mix(col,texCol,0.8);
}
