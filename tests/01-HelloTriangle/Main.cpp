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

	Geometry gt = makeNGon(90000, 1);

	Geometry gb = makeCheckerboard(3, .2f);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vPos;\n"
		"out vec4 vColor;\n"
		"void main () { gl_Position = position; vPos = position; vColor = color; }\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec4 vPos;\n"
		"in vec4 vColor;\n"
		"void main () { outColor = vColor;}\n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 800 };

	while (context.step())
	{
		s0_draw(f, s, gb);
	}

	freeGeometry(g);
	freeShader(s);

	context.term();

	return 0;
}