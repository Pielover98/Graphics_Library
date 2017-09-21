#include"graphics\Context.h"
#include"graphics\RenderObjects.h"
#include"graphics\Vertex.h"
#include"graphics\draw.h"
#include"graphics\genShape.h"
#include "graphics\load.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(800, 800);


	Vertex vquad[] =
	{
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1, 1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/sphere.obj");

	Texture tex = loadTexture("../../resources/textures/globe.jpg");

	//Shader sq = loadShader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");

	Shader scube = loadShader("../../resources/shaders/cube.vert", "../../resources/shaders/cube.frag");


	Framebuffer screen = { 0, 800, 800 };


	float x = 0, y = 0;
	while (context.step())
	{
		clearFramebuffer(screen);
		float time = context.getTime();

		int frame = 3;
		frame += context.getKey('w') * 3;
		frame += context.getKey('A') * 2;
		frame += context.getKey('D') * 1;
		frame %= 4;

		x += context.getKey('D') * 0.16;
		y += context.getKey('W') * 0.16;
		x += context.getKey('A') * 0.16;
		y += context.getKey('S') * 0.16;

	

		int loc = 0, tslot = 0;


		//setUniforms(sq, loc, tslot, tex, (int)(time*3) % 4 + frame * 4, 4, 4, x, y);
		//s0_draw(screen, sq, quad);

		glm::mat4 mod_cube = glm::rotate(time, glm::vec3(1, 1, 1));

		setFlags(RenderFlag::DEPTH);


		loc = 0, tslot = 0;
		setUniforms(scube, loc, tslot, mod_cube, tex);
		s0_draw(screen, scube, cube);

	}


	context.term();
	return 0;

}