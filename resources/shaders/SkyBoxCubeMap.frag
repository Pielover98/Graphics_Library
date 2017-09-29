#version 450
layout(location = 3) uniform samplerCube skybox;

in vec3 vPos;

out vec4 outColor;

void main()
{
	outColor = texture(skybox, vPos);
}

