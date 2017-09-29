#pragma once
#pragma once
#include "RenderObjects.h"
#include <iostream>
#include <string>
class Assets
{
public:

	Skybox loadSkybox(std::string name);
	Geometry loadGeo(std::string name);
	Texture loadTexture(std::string name);
	Shader loadShaderAsset(std::string name, std::string name2);


};