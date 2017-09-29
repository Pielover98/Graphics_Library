#version 450

in vec2 vUV;
in vec4 vNormal;
layout (location = 3) uniform sampler2D diffuse;

out vec4 outColor;

void main()
{
	vec3 L = normalize(vec3(1,-1,0));
	vec3 N = vNormal.xyz;

	float lamb = dot(N,-L);
	outColor = lamb*texture(diffuse, vUV);

}