#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexcoord;

out vec3 worldpos;
out vec2 texcoord;
out vec3 normal;

uniform mat4 model;
uniform mat4 model_outline;
uniform mat4 view;
uniform mat4 perspective;
uniform mat4 normalmat;
uniform bool outline_vert;

void main()
{
	if(outline_vert==false)
	{
		gl_Position=perspective * view * model * vec4(aPos,1.0);
		worldpos=vec3(model * vec4(aPos,1.0));
	}
	if(outline_vert==true)
	{
		vec4 pos=perspective * view * model_outline * vec4(aPos+aNormal*2.8,1.0);
		pos.z=0.99f;
		gl_Position=pos.xyzw;

	}
	normal=mat3(normalmat)*aNormal;
	texcoord=aTexcoord;
}