#pragma once

#include "glm\glm.hpp"

struct  Vertex
{
	glm::vec4 position; // 16 bytes for position starting at address 0
	glm::vec4 color;

	glm::vec2 UV;
	glm::vec4 normals;

	glm::vec4 tangent;
	glm::vec4 bitangent;
};