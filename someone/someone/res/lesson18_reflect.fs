#version 330 core

uniform vec3 u_CameraPos;
uniform samplerCube u_SkyBoxTexture;

in vec3 FragPos;
in vec3 FragNormal;

out vec4 FragColor;

void main()
{
    vec3 inputDir = normalize(FragPos - u_CameraPos);
    vec3 normalDir = normalize(FragNormal);
    vec3 sampleDir = reflect(inputDir,normalDir);
    FragColor = vec4(texture(u_SkyBoxTexture,sampleDir).rgb,1.0);
}
