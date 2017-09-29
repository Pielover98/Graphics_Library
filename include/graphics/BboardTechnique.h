#pragma once
#include"glm/ext.hpp"
#include "glinc.h"
class BboardTechnique //: public Technique
{
public:
	BboardTechnique();

	virtual bool Init();

	void SetVP(const glm::mat4& VP);
	void SetCameraPosition(const glm::vec3& Pos);
	void SetColorTextureUnit(unsigned int TextureUnit);

private:

	GLuint m_VPLocation;
	GLuint m_cameraPosLocation;
	GLuint m_colorMapLocation;

};