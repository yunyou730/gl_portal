#version 330 core

uniform sampler2D u_Tex1;
uniform sampler2D u_Tex2;

in vec2 UV;
out vec4 FragColor;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    float linearDepth = (2.0 * near * far) / (far + near - z * (far - near));
    return linearDepth;
}


void main()
{
//    vec4 colorFromTexture1 = texture(u_Tex1,UV);
//    vec4 colorFromTexture2 = texture(u_Tex2,UV);
//    FragColor = colorFromTexture1 + colorFromTexture2;
    
//    float depth = LinearizeDepth(gl_FragCoord.z);
//    FragColor = vec4(vec3(depth),1.0);
    
    FragColor = vec4(0.94,0.28,0.26,1.0);
}
