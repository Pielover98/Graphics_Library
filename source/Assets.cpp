#include "graphics\Assets.h"
#include "graphics\Load.h"

Skybox Assets::loadSkybox(std::string name)
{

	return Skybox();
}

Geometry Assets::loadGeo(std::string name)
{
	std::string asset = "../../resources/models/";

	asset += name;
	return loadGeometry(asset.c_str());
}

Texture Assets::loadTexture(std::string name)
{

	const char* asset = "../../resources/textures/";
	name += asset;
	return loadTexture(name);
}

Shader Assets::loadShaderAsset(std::string name, std::string name2)
{

	std::string asset = "../../resources/shaders/";

	std::string asset2 = "../../resources/shaders/";

	asset += name;
	asset2 += name2;

	return loadShader(asset.c_str(), asset2.c_str());
}
