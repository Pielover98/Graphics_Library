#version 450 
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 UV;

out vec2 vUV;
out vec4 ParticleColor;
layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform vec2 offset;
layout (location = 2) uniform vec4 color;

void main()
{

	float scale = 10.0f;
	vUV = UV;
	ParticleColor = color;
	gl+Position = projection * vec4((UV * scale) + offset, 0.0,1.0);



}