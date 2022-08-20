#version 330 core

in vec2 v_UV;
out vec4 FragColor;

uniform sampler2D u_ShadowMap;

uniform float isPersp;
uniform float nearPlane;
uniform float farPlane;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void main()
{
//    gl_FragDepth = gl_FragCoord.z;
//    FragColor = vec4(vec3(gl_FragCoord.z),1.0);
    vec4 col = texture(u_ShadowMap,v_UV);
    
    if(isPersp > 0.0)
    {
        col.r = LinearizeDepth(col.r);
//        col.g = LinearizeDepth(col.g);
//        col.b = LinearizeDepth(col.b);
//        col.a = LinearizeDepth(col.a);
        FragColor = vec4(vec3(LinearizeDepth(col.r) / farPlane),1.0);
    }
    else
    {
        FragColor = col;//vec4(v_UV.x,v_UV.y,0.0,1.0);
    }
}

