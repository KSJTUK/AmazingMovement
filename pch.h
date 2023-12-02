#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtx/euler_angles.hpp>
#include <gl/glm/gtx/vector_angle.hpp>
#include <gl/glm/gtc/quaternion.hpp>	

#include <random>
#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <utility>
#include <list>

#include "Util/stb_image.h"


using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using byte = unsigned char;

struct Vertex {
	glm::vec3 position{ };
	glm::vec2 texture{ };
	glm::vec3 normal{ };
};

struct Meterial {
	glm::vec3 ambient{ 1.f };
	glm::vec3 diffuse{ 0.5f };
	glm::vec3 specular{ 1.f }; // 하이라이트 정도를 조절
	float shininess{ 32.f };     // 하이라이트의 범위(카메라가 감지하는 하이라이트의 범위)조절
};

struct TextureInfo {
	uint32 id{ };
	int32 width{ };
	int32 height{ };
	int32 nrChannel{ };
};

struct CubeMapInfo {
	enum { SIZE = 6 };
	uint32 id{ };
	int32 width[SIZE]{ };
	int32 height[SIZE]{ };
	int32 nrChannel[SIZE]{ };
};

// 생성할 윈도우의ㅡ 정보를 담을 구조체 정의
struct WindowInfo {
	int x;
	int y;
	int width;
	int height;
	float fWidth;
	float fHeight;
	char* windowTitle;
};

extern std::unique_ptr<class Engine> engine;
extern std::unique_ptr<class RandomEngine> randomEngine;

namespace constants {
	extern float gravity;
	extern float epsilon;
};

#define OBJECTSHADER ObjectShader::GetInstance()
#define LIGHTOBJECTSHADER LightObjectShader::GetInstance()
#define PARTICLESHADER ParticleShader::GetInstance()
#define TERRAINSHADER TerrainShader::GetInstance()
#define BACKGROUNDSHADER BackGroundShader::GetInstance()
#define MODELLIST ModelList::GetInstance()