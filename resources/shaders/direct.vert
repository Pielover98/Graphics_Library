#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 UV;
layout(location = 3) in vec4 normals;

layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

out vec4 vPos;
out vec2 vUV;

void main()
{

	vUV = UV;
	vPos = model * position;
	gl_Position = proj * view * model * position;


}