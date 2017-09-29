#pragma once

#include <iostream>
#include <string>
#include "glinc.h"
#include "RenderObjects.h"
#include "glm/ext.hpp"
#include "BboardTechnique.h"
class BboardList
{

public:
	BboardList();
	~BboardList();

	bool Init(const std::string& TexFileName);

	void Render(const glm::mat4& VP, const glm::vec3& CamPos);

private:
	void CreatePositionBuffer();

	GLuint m_VP;
	Texture* m_pTexture;
	BboardTechnique m_technique;

};

