#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 UV;

out vec2 vUV;


void main()
{

	gl_Position = position;
	vUV = UV;

}