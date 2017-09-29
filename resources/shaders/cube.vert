#version 450


layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 0) uniform mat4 model;
layout(location = 2) in vec2 UV;
layout(location = 3) in vec4 norm;
out vec4 vColor;
out vec4 vNormal;
out vec2 vUV;
out vec4 vPos;
//out vec4 ObjectPosition;
void main ()
{
	gl_Position = model * position;
	vNormal = model * norm;
	
//	vNormal = normalize(vec4(gl_Position.xyz,0));
	vColor = position;
	vPos = model * position;
	
  //  ObjectPosition = ObjectPos;
	vUV = UV;
	
}