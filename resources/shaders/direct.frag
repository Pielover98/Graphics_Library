#version 450 

layout(location = 3) uniform mat4 lproj;
layout(location = 4) uniform mat4 lview;
layout(location = 5) uniform sampler2D shadowmap;
layout(location = 6) uniform vec4 color;

layout(location = 7) uniform mat4 lproj2;
layout(location = 8) uniform mat4 lview2;
layout(location = 9) uniform vec4 color2;
in vec2 vUV;
in vec4 vPos;

uniform float shadowBias = 0.01;

//simple matrix that convers clip space (-1,1) to UV space(0,1)
uniform mat4 clipToUV = mat4(0.5f, 0.0f, 0.0f, 0.0f,
							 0.0f, 0.5f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.5f, 0.0f,
							 0.5f, 0.5f, 0.5f, 1.0f);

							 
float pcf(in sampler2D shadowMap, in vec4 shadowPosition, int iterations);

out vec4 outColor;

void main()
{
	vec4 sUV = clipToUV * lproj * lview * vPos;

	float visibility = 1;

	if(texture(shadowmap,sUV.xy).r < sUV.z - shadowBias)
	{
	visibility = pcf(shadowmap,sUV,16);
	}
	
	vec4 sUV2 = clipToUV * lproj2 * lview2 * vPos;

	float visibility2 = 1;

	if(texture(shadowmap,sUV2.xy).r < sUV2.z - shadowBias)
	{
	visibility2 = pcf(shadowmap,sUV,16);
	}

	outColor = color * visibility + color2 * visibility2;
}

float pcf(in sampler2D shadowMap, in vec4 shadowPosition, int iterations)
{

	vec2 sDim = textureSize(shadowMap,0).xy;
	float retval; 
	vec2 uv = shadowPosition.xy;
	float z = shadowPosition.z - .01;

	for(int i = -iterations; i <= iterations; i++)
	{
		if(!(texture(shadowMap,uv+vec2(i,0)/sDim).r < z))
		{
			retval++;
		}

		if(!(texture(shadowMap,uv+vec2(0,i)/sDim).r < z))
		{
			retval++;
		}
	}

	return retval / (iterations*4);

}
