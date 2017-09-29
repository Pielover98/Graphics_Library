#define GLM_FORCE_SWIZZLE

#include "graphics/glinc.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"

#ifdef  _DEBUG
#include <iostream>
#endif //  _DEBUG


glm::vec4 calcTangent(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{

	glm::vec4 p1 = v1.position - v0.position;
	glm::vec4 p2 = v2.position - v0.position;

	glm::vec2 t1 = v1.UV - v0.UV;
	glm::vec2 t2 = v2.UV - v0.UV;

	return glm::normalize((p1*t2.y - p2*t1.y) / (t1.x*t2.y - t1.y*t2.x));
	//UV.x will follow the tangents
	//UV.y will follow the bitangents

}

void solveTangents(Vertex * v, size_t vsize, const unsigned* idxs, size_t isize)
{
	for (int i = 0; i < isize; i += 3)
	{
		glm::vec4 T = calcTangent(v[idxs[0]], v[idxs[1]], v[idxs[2]]);

		for (int j = 0; j < 3; j++)
		{
			v[idxs[i + j]].tangent = glm::normalize(T + v[idxs[i + j]].tangent);
		}
	}

	for (int i = 0; i < vsize; i++)
	{
		v[i].bitangent = glm::vec4(glm::cross(v[i].normals.xyz(), v[i].tangent.xyz()), 0);
	}
}

Geometry makeGeometry(const Vertex * vertices, size_t vsize, const unsigned * indicies, size_t isize)
{
	Geometry retval = { 0,0,0,isize };

	//Declare our openGL objects and acquire handles
	glGenBuffers(1, &retval.vbo);
	glGenBuffers(1, &retval.ibo);
	glGenVertexArrays(1, &retval.handle);

	// scope the variavles
	glBindVertexArray(retval.handle);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo);

	//init all buffers
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(unsigned), indicies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16); // bytes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32); // bytes
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)40); // bytes
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)56); // bytes
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)72); // bytes


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	return retval;
}

void freeGeometry(Geometry & g)
{

	glDeleteBuffers(1, &g.vbo);
	glDeleteBuffers(1, &g.ibo);
	glDeleteVertexArrays(1, &g.handle);
	g = { 0,0,0,0 };

}



Shader MakeShader(const char * vert_src, const char * frag_src)
{
	Shader retval = { 0 };

	retval.handle = glCreateProgram();

	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vert_src, 0);
	glShaderSource(fs, 1, &frag_src, 0);

	glCompileShader(vs);
	glCompileShader(fs);

#ifdef  _DEBUG
	GLint success = GL_FALSE;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(vs, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;

	}

	success = GL_FALSE;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(fs, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}
#endif //  _DEBUG

	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);


#ifdef  _DEBUG
	success = GL_FALSE;
	glGetProgramiv(retval.handle, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetProgramInfoLog(retval.handle, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;

	}

#endif //  _DEBUG


	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader &s)
{
	glDeleteProgram(s.handle);
	s = { 0 };
}

// 4 RGBO = 4 channels
// 512x512 image = 262144 pixels * 4 channels = 1million

Texture MakeTexture(unsigned w, unsigned h, unsigned c, const void* pixels, bool isFloat)
{

	Texture retval = { 0 };

	GLenum f = 0, i = 0; // externam and internal

	switch (c)
	{
	case 0:
		f = GL_DEPTH_COMPONENT;
		i = GL_DEPTH24_STENCIL8;
		break;
	case 1:
		f = GL_RED;
		i = GL_R32F;
		break;
	case 2:
		f = GL_RG;
		i = GL_RG32F;
		break;
	case 3:
		f = GL_RGB;
		i = GL_RGB32F;
		break;
	case 4:
		f = GL_RGBA;
		i = GL_RGBA32F;
		break;
	}

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	i = ((isFloat || c == 0) ? i : f);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, i, w, h, 0, f, (isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE), pixels);


	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}

void freeTexture(Texture & t)
{
	glDeleteTextures(1, &t.handle);
	t = { 0 };
}

Framebuffer makeFramebuffer(unsigned w, unsigned h, unsigned c, bool hasDepth, unsigned nColorTargets, unsigned nFloatTargets)
{
	Framebuffer retval = { 0,w,h,0,0,{ 0 } };
	retval.nTargets = nColorTargets + nFloatTargets;

	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);
	if (hasDepth)
	{
		retval.depthTarget = MakeTexture(w, h, 0, 0, 0);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depthTarget.handle, 0);
	}

	const GLenum attachments[8] =
	{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };

	for (int i = 0; i < retval.nTargets && i < 8; i++)
	{

		retval.targets[i] = MakeTexture(w, h, c, 0, i >= nColorTargets);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.targets[i].handle, 0);

	}

	glDrawBuffers(retval.nTargets, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return retval;
}

ParticleBuffer makeParticleBuffer(const ParticleBuffer * parts, size_t psize)
{

	ParticleBuffer Retval = { 0 };

	const int ParticleCount = 100000;



	// Create VBO for input on even-numbered frames and output on odd-numbered frames:

	glGenBuffers(1, &Retval.vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Retval.vbo[0]);
	glGenTransformFeedbacks(0, &Retval.handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parts) * psize, &psize, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	// Create VBO for output on even-numbered frames and input on odd-numbered frames:

	glGenBuffers(1, &Retval.vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, Retval.vbo[1]);
	glGenTransformFeedbacks(0, &Retval.handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parts) * psize, &psize, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return Retval;
}



Shader makeUpdateShader(const char * vert_src)
{

	return Shader();
}
