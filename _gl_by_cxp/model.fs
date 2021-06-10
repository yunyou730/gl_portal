#version 330 core
in vec2 texcoord;
in vec3 normal;
in vec3 worldpos;
out vec4 Fragcolor;

struct Material{
	sampler2D texture_diffuse1;//物体颜色
	sampler2D texture_specular1;//高光贴图
	sampler2D texture_ambient1;//反射贴图
	float shininess;
};

struct SpotLight{
	vec3 position;
	vec3 spot_direction;
	float cos_cutoff_in;
	float cos_cutoff_out;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
};
struct DirLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight{
	vec3 position;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointlights[NR_POINT_LIGHTS];
uniform DirLight dirlight;
uniform SpotLight spotlight; 
uniform Material material;
uniform vec3 viewpos;
uniform bool outline_frag;
uniform vec3 outline_color;
uniform samplerCube cubemap;

vec3 DirLightColor(DirLight light, vec3 posnormal, vec3 viewdir){
	vec3 lightdir=normalize(-light.direction);
	//float NL=dot(posnormal,-lightdir);
	//float it=(1.0+NL)/2.0;
	//vec3 objColor=texture(material.texture_diffuse1, texcoord);
	//vec3 kBlue=vec3(0.0,0.0,1.0);
	//vec3 kYellow=vec3(1.0,1.0,0.0);
	//vec3 kCool= kBlue+0.2*objColor;
	//vec3 kWarm= kYellow+0.6*objColor;
	//return (it*kCool+(1.0-it)*kWarm);


	vec3 ambient=light.ambient * vec3(texture(material.texture_diffuse1, texcoord));
	float diff=max(dot(lightdir,posnormal),0.0);
	vec3 diffuse=light.diffuse * vec3(texture(material.texture_diffuse1, texcoord)) * diff;
	vec3 reflectdir=reflect(-lightdir,posnormal);
	float spec= pow(max(dot(viewdir,reflectdir),0.0),material.shininess);
	vec3 specular=light.specular * vec3(texture(material.texture_specular1, texcoord)) * spec;
	return (ambient + diffuse + specular);


}

vec3 AmbientColor(samplerCube cube){

	vec3 I=normalize(worldpos-viewpos);
	vec3 R=reflect(I, normalize(normal));
	vec3 cube_color=texture(cube, R).rgb;
	vec3 ambient=cube_color * 0.5 * vec3(texture(material.texture_diffuse1, texcoord));
	vec3 diffuse=cube_color * 0.6 * vec3(texture(material.texture_diffuse1, texcoord));
	vec3 specular=cube_color * vec3(texture(material.texture_ambient1,texcoord));
	return (ambient + diffuse + specular);
}

vec3 SpotLightColor(SpotLight light,vec3 posnormal, vec3 viewdir){
	vec3 lightdir=normalize(light.position-worldpos);
	vec3 lightdir_topos=-lightdir;
	float distance=length(light.position-worldpos);
	float cos_theta=dot(lightdir_topos,normalize(light.spot_direction));
	float epsilon=light.cos_cutoff_in - light.cos_cutoff_out;
	float spotlight_i=clamp((cos_theta-light.cos_cutoff_out)/epsilon + 0.5f,0.0,1.0);
	float attenuation=1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	float diff=max(dot(posnormal,lightdir),0.0f);
	vec3 reflectdir=reflect(lightdir_topos,posnormal);
	float spec=pow(max(dot(viewdir,reflectdir),0.0f),material.shininess);
	vec3 ambient=light.ambient * vec3(texture(material.texture_diffuse1,texcoord));
	vec3 diffuse=light.diffuse * vec3(texture(material.texture_diffuse1,texcoord)) * diff;
	vec3 speculartex=vec3(texture(material.texture_specular1,texcoord));
	vec3 specular=light.specular * speculartex * spec;
	ambient *= attenuation;
	diffuse *= attenuation * spotlight_i;
	specular *= attenuation * spotlight_i;
	return (ambient + diffuse + specular);
}

vec3 PointLightColor(PointLight light, vec3 posnormal, vec3 viewdir){
	vec3 lightdir=normalize(light.position-worldpos);
	vec3 lightdir_topos=-lightdir;
	float distance=length(light.position-worldpos);
	float attenuation=1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	float diff=max(dot(posnormal,lightdir),0.0f);
	vec3 reflectdir=reflect(lightdir_topos,posnormal);
	float spec=pow(max(dot(viewdir,reflectdir),0.0f),material.shininess);
	vec3 ambient=light.ambient * vec3(texture(material.texture_diffuse1,texcoord));
	vec3 diffuse=light.diffuse * vec3(texture(material.texture_diffuse1,texcoord)) * diff;
	vec3 speculartex=vec3(texture(material.texture_specular1,texcoord));
	vec3 specular=light.specular * speculartex * spec;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}
void main(){
	if(outline_frag==false)
	{
	vec3 norm=normalize(normal);
	vec3 viewDir=normalize(viewpos-worldpos);
	vec3 outputcolor=vec3(0.0,0.0,0.0);

	outputcolor+=DirLightColor(dirlight,norm,viewDir);
	outputcolor += SpotLightColor(spotlight,norm,viewDir);
	outputcolor += AmbientColor(cubemap);
	for(int i=0;i<NR_POINT_LIGHTS;i++)
		outputcolor += PointLightColor(pointlights[i],norm,viewDir);


	Fragcolor=vec4(outputcolor,1.0);
	}
	if(outline_frag==true)
	Fragcolor=vec4(outline_color,1.0);
}














