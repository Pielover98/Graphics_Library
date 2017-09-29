#pragma once
#include "graphics\RenderObjects.h"
#include "glm/glm.hpp"
#include "glm\ext.hpp"
struct Camera
{
	glm::mat4 proj;
	glm::mat4 view;
};

struct SpecGloss
{
	Geometry geo;
	glm::mat4 model;

	Texture diffuse;
	Texture specular;
	Texture normal;
	float gloss;

};

struct StandardLight
{
	glm::vec3 direction;
	glm::vec4 color;
	float intensity;
	glm::vec4 ambient;
	int type;
};

struct DirectionalLight
{
	glm::vec3 target; // for shadow mapping
	glm::vec3 direction;
	float range;

	glm::vec4 color;
	float intensity;

	glm::mat4 getProj() const
	{
		return glm::ortho<float>(-range, range, -range, range, -range, range);
	}
	glm::mat4 getView() const
	{
		return glm::lookAt(direction, target, glm::vec3(0, 1, 0));
	}

	// view
	//project
	//color
	//intensity


};

namespace _internal
{

	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Camera &val);

	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const SpecGloss &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const DirectionalLight &val);

}