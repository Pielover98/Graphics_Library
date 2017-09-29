#pragma once
#include <iostream>
#include "glm\ext.hpp"
#include "glinc.h"


class Particles
{
public:
	Particles();

	~Particles();

	bool initParticles(const glm::vec3& Pos);

private:

	bool m_isFirst;

	unsigned int m_currVB; 
	unsigned int m_currTFB; 

	GLuint m_particleBuffer[2];
	GLuint m_transformFeedback[2];


};