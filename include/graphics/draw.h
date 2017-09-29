#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;
#include "glm\fwd.hpp"

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);


void tf0_update(const Shader &s, const ParticleBuffer &pb, int active);

void tf0_draw(const Framebuffer &s, const Shader &sp, const ParticleBuffer &pb);


void setUniform(const Shader &s, int location, float value);
void setUniform(const Shader &s, int location, int value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);


// called eaqch time the variadic unpacking recursion takes place
// based upon what uniforms are passed in, thje correct function will be called
// in so doing the appropriate glprogramuniform function will be called
namespace _internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Skybox &val);
	void t_setUniform(const Shader &s, int &location, int &tex_io, const glm::vec2 &value);
	void t_setUniform(const Shader &s, int &location, int &tex_io, const glm::vec4 &value);
	void t_setUniform(const Shader &s, int &location, int &tex_io, const glm::vec3 &value);
	void t_setUniform(const Shader &s, int &location, int &tex_io, const glm::mat4 &value);
}

//the recursive template function
// U is a variadic template parameter. each time the function gets called,
// the T param val will comsume 1 element of the variadic
// so if there is recursion function calling itself, the uniform will slowly be eaten by T
template<typename T, typename ...U>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val, U &&... uniforms)
{
	_internal::t_setUniform(s, loc_io, tex_io, val);

	//note the t param isnt part of this call
	//it is stealing val from uniforms variadic
	setUniforms(s, loc_io, tex_io, uniforms...);
}

//this base case is the last function that gets called, since t is always eating 
//values from U, eventually there will be no more U, to ensure that we have valid function
// we need to have base call like so
template<typename T>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val)
{
	_internal::t_setUniform(s, loc_io, tex_io, val);
}


enum RenderFlag
{

	NONE = 0,
	DEPTH = 1,
	ADDITIVE = 2
};

void setFlags(int flags);

void clearFramebuffer(const Framebuffer & r, bool color = true, bool depth = true);