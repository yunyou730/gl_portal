#version 330 core

in vec2 v_UV;
out vec4 FragColor;

uniform sampler2D u_ShadowMap;

void main()
{
//    gl_FragDepth = gl_FragCoord.z;
//    FragColor = vec4(vec3(gl_FragCoord.z),1.0);
    vec4 col = texture(u_ShadowMap,v_UV);
    FragColor = col;//vec4(v_UV.x,v_UV.y,0.0,1.0);
}

