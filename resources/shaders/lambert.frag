#version 450

layout (location = 3) uniform sampler2D diffuse;
layout (location = 4) uniform vec3 LP;
layout (location = 5) uniform vec4 lightColor;

in vec2 vUV;
in vec3 vNormal;
in vec3 vPos;
out vec4 outColor;
void main()
{
	vec4 surfaceColor = texture(diffuse, vUV);
	
	vec3 DISP = vPos - LP;

	float d = length(DISP);
	float a = 1.0/(d * d);
	vec3  L = normalize(DISP);
	vec3  N = vNormal;

	float labertianFactor = max(0,dot(N, -L));

	vec4 lambertianTerm = surfaceColor * labertianFactor * lightColor;

	outColor = lambertianTerm;	
	//outColor = vec4(0,1,0,0);	

}