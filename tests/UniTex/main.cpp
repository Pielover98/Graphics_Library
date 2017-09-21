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

	Geometry gt = makeNGon(90000, .5f);

	Geometry gb = makeCheckerboard(3, .2f);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 uv;\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform int key;\n"
		"out vec4 vPos;\n"
		"out vec4 vColor;\n"
		"out vec2 vUV;\n"
		"void main () { gl_Position = position; vPos = position; vUV = uv; vColor = (key == 1)?color:1-color; gl_Position.x += cos(time*2)/2.0;gl_Position.y += abs(sin(time*5)/2.0); vUV = position.xy; }\n";

	const char* fsource =
		"#version 450\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 4) uniform sampler2D map;\n"
		"out vec4 outColor;\n"
		"in vec4 vPos;\n"
		"in vec4 vColor;\n"
		"in vec2 vUV;"
		"void main () { vec2 uv = vUV; uv.x += sin(time); uv.y += cos(time + uv.x); outColor = texture(map, vUV * sin(time * 1 + 5.0) + 5.0); }\n";

	

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 1000, 1000 };

	unsigned char pixels[] = { 255,0,255,
		0,255,0,255,
		0,255,0,255,255,0 }; 

	Texture t_magyel = makeTexture(2, 1, 3, pixels);
	Texture t_mask = makeTexture(3, 2, 4, pixels);

	while (context.step())
	{
		clearFramebuffer(f);
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 1, (int)context.getKey('A'));

		setUniform(s, 4, t_magyel, 0);
		setUniform(s, 5, t_mask, 1);
		 
		s0_draw(f, s, gb);
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);

	context.term();

	return 0;
}