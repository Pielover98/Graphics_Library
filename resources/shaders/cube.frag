#version 450
layout(location = 1) uniform sampler2D map;
out vec4 outColor;
in vec2 vUV;
in vec4 vColor;
in vec4 vNormal;
in vec4 vPos;
layout(location = 2) uniform vec4 ObjectPos;

void main ()
{
	
	outColor = texture(map, vUV.xy);
	if(ObjectPos != vec4(0,0,0,1))
	{
	outColor = dot(-normalize(vec4(0,0,1,0)), vNormal) * outColor;
	}
	else
	{
	outColor = dot(-normalize(vec4(0,0,1,0)), vNormal) * outColor;
	}
	outColor.a = 1;

}