#version 330 core


struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};


uniform Material material;


//in vec2 uv;

out vec4 FragColor;

void main()
{
    vec3 colorDiffuse = vec3(texture(material.texture_diffuse1,vec2(0.0,0.0)));
//    vec3 colorSpecular = texture(material.texture_specular1,uv);
    FragColor = vec4(1.0,1.0,1.0,1.0);
}

