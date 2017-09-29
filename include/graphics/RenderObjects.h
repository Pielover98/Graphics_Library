#pragma once
#include "glm\ext.hpp"
struct  Vertex;
struct Geometry
{
	unsigned handle, // Vertex array object
		vbo,    // vertex buffer
		ibo,    // Index Buffer
		size;   // how many indicies make up this model
};

Geometry makeGeometry(const Vertex* vertices, size_t vsize,
	const unsigned* indicies, size_t isize);

void freeGeometry(Geometry &g);


void solveTangents(Vertex* v, size_t vsize,
	const unsigned* idxs, size_t isize);

struct Shader
{
	unsigned handle;
};

Shader MakeShader(const char* vert_src, const char* frag_src);

void freeShader(Shader &s);



struct Texture
{

	unsigned handle;


};

Texture MakeTexture(unsigned w, unsigned h, unsigned c, const void* pixels, bool isFloat = false);

void freeTexture(Texture &t);

struct Framebuffer
{
	unsigned handle,
		width,
		height,
		nTargets;

	Texture depthTarget;
	Texture targets[8];
};



Framebuffer makeFramebuffer(unsigned w, unsigned h, unsigned c,
	bool hasDepth, unsigned nTargets, unsigned nFloatTargets);

struct Skybox
{
	unsigned handle;
};

struct ParticleVertex
{
	glm::vec4 position;
	glm::vec3 velocity;
	glm::vec4 color;
};

struct ParticleBuffer { unsigned handle[2], vbo[2], size; };

ParticleBuffer makeParticleBuffer(const ParticleBuffer* parts, size_t psize);

Shader makeUpdateShader(const char* vert_src);
