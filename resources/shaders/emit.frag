#version 450

in vec2 vUV;
in vec4 ParticleColor;
out vec4 outColor;

layout (location = 3) uniform sampler2D sprite;

void main()
{

 color = (texture(sprite, vUV) * ParticleColor);

}