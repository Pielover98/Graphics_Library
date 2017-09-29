#pragma once

#include "RenderObjects.h"


#include <cstdio>
#include <vector>

Texture loadTexture(const char* path);

Shader loadShader(const char* vpath, const char* fpath);

Geometry loadGeometry(const char* path);


Shader loadUpdateShader(const char* vert_path);


Skybox loadCubemap(std::vector<std::string> faces);