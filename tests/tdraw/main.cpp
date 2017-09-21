#include"graphics\Context.h"
#include"graphics\RenderObjects.h"
#include"graphics\Vertex.h"
#include"graphics\draw.h"
#include"graphics\genShape.h"


int main()
{
	Context context;
	context.init(1000, 1000);


	Vertex verts[4] = { { { -.5f,-.5f, 0, 1 },{ 0,1,1,1 } },
	{ { .5f,-.5f, 0, 1 },{ 0,.5f,1,1 } },
	{ { .5f, .5f, 0, 1 },{ 1,0,1,1 } },
	{ { -.5f,.5f, 0, 1 },{ 0,1,.5f,1 } } };

	unsigned idxs[6] = { 0,1,2,0,2,3 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);

	Framebuffer f = { 0, 1000, 1000 };

	unsigned char pixels[] = { 255,0,255,
		0,255,0,255,
		0,255,0,255,255,0 };



	Texture t_magyel = makeTexture(2, 1, 3, pixels);
	Texture t_mask = makeTexture(3, 2, 4, pixels);


	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 uv;\n"
		"out vec2 vUV;\n"
		"void main()\n"
		"{\n"
		"gl_Position = position;\n"
		"vUV = uv;\n"
		"}\n";



	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec2 vUV;"
		"layout(location = 0) uniform sampler2D map;\n"
		"layout(location = 1) uniform float time;\n"
		"layout(location = 2) uniform int key;\n"
		"void main()\n"
		"{\n"
		"outColor = texture(map, vUV);\n"
		"}\n";




	Shader s = makeShader(vsource, fsource);



	while (context.step())
	{
		int loc = 0, tex = 0;
		setUniforms(s, loc, tex, t_magyel, (float)context.getTime(), (int)context.getKey(' '));
		s0_draw(f, s, g);

	}

	freeTexture(t_magyel);
	freeTexture(t_mask); 
	freeGeometry(g);
	freeShader(s);
	context.term();
}