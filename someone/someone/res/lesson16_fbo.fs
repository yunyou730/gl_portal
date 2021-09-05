#version 330 core

uniform sampler2D u_FramebufferTexture;

in vec2 UV;
out vec4 FragColor;

uniform int u_PostProcessIndex = 0;
uniform float u_BlurFactor;

vec4 Origin()
{
    return texture(u_FramebufferTexture,UV);
}


vec4 InverseColor()
{
    return vec4(vec3(1.0 - texture(u_FramebufferTexture,UV)),1.0);
}

vec4 Gray()
{
    vec4 col = texture(u_FramebufferTexture,UV);
    float avg = (col.r + col.g + col.b) / 3.0;
    return vec4(avg,avg,avg,1.0);
}

vec4 Sharpen()
{
    float offset = 1.0 / 300.0 * u_BlurFactor;

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );

    float kernel[9] = float[](
        -1.0, -1.0, -1.0,
        -1.0,  9.0, -1.0,
        -1.0, -1.0, -1.0
    );

    vec3 col = vec3(0.0);
    for(int i = 0;i < 9;i++)
    {
        vec3 sampleCol = vec3(texture(u_FramebufferTexture,UV + offsets[i]));
        col += sampleCol * kernel[i];
    }

    return vec4(col, 1.0);
}

vec4 Blur()
{
    float offset = 1.0 / 300.0 * u_BlurFactor;
    
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );

    float kernel[9] = float[](
      1.0 / 16, 2.0 / 16, 1.0 / 16,
      2.0 / 16, 4.0 / 16, 2.0 / 16,
      1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec3 col = vec3(0.0);
    for(int i = 0;i < 9;i++)
    {
        vec3 sampleCol = vec3(texture(u_FramebufferTexture,UV + offsets[i]));
        col += sampleCol * kernel[i];
    }

    return vec4(col, 1.0);
    
}

vec4 Edge()
{
    float offset = 1.0 / 300.0 * u_BlurFactor;
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );

    float kernel[9] = float[](
        1.0, 1.0, 1.0,
        1.0,-8.0, 1.0,
        1.0, 1.0, 1.0
    );

    vec3 col = vec3(0.0);
    for(int i = 0;i < 9;i++)
    {
        vec3 sampleCol = vec3(texture(u_FramebufferTexture,UV + offsets[i]));
        col += sampleCol * kernel[i];
    }

    return vec4(col, 1.0);
}



void main()
{
    if(u_PostProcessIndex == 0)
    {
        FragColor = InverseColor();
    }
    else if(u_PostProcessIndex == 1)
    {
        FragColor = Gray();
    }
    else if(u_PostProcessIndex == 2)
    {
        FragColor = Sharpen();
    }
    else if(u_PostProcessIndex == 3)
    {
        FragColor = Blur();
    }
    else if(u_PostProcessIndex == 4)
    {
        FragColor = Edge();
    }
    else if(u_PostProcessIndex == 5)
    {
        FragColor = Origin();
    }
}
