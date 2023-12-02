#include "pch.h"
#include "AnimationCubes.h"
#include "Object/Cube.h"
#include "Graphics/Shader.h"
#include "Util/RandomEngine.h"

AnimationCubes::AnimationCubes(const float xzMapSize, const glm::uvec2& numOfCubes) : m_mapSize{ xzMapSize }, m_numCubes{ numOfCubes } {
	glm::vec3 initColor{ 0.f, 1.f, 0.f };
	m_cubes.resize(m_numCubes.y);

	float width = m_mapSize / m_numCubes.x;
	float height = m_mapSize / m_numCubes.y;
	// 카메라 기준 왼쪽 위
	glm::vec2 leftTop{ -width * (m_numCubes.x / 2.f), -height * (m_numCubes.y / 2.f) };

	for (uint32 z = 0; z < m_numCubes.y; ++z) {
		for (uint32 x = 0; x < m_numCubes.x; ++x) {
			float randomYScale = randomEngine->GetRandFloat(m_scaleRange.first, m_scaleRange.second);
			float randomSpeed = randomEngine->GetRandFloat(m_animationSpeedRange.first, m_animationSpeedRange.second);
			glm::vec3 scale{ width, randomYScale, height };
			glm::vec3 position{ leftTop.x + width * x, 0.f, leftTop.y + height * z };

			m_cubes[z].emplace_back(initColor, position, scale);
			m_cubes[z].back().SetAnimationOption(m_scaleRange, randomSpeed);
		}
	}
}

AnimationCubes::~AnimationCubes() { }

void AnimationCubes::SetScaleRange(const float& min, const float& max) {
	m_scaleRange = { min, max };
}

void AnimationCubes::SetRandomScaleAnimation()
{
}

void AnimationCubes::Update(float deltaTime) {
	for (auto& cubeVec : m_cubes) {
		for (auto& cube : cubeVec) {
			cube.Update(deltaTime);
		}
	}
}

void AnimationCubes::Render() {
	OBJECTSHADER->UseProgram();
	for (auto& cubeVec : m_cubes) {
		for (auto& cube : cubeVec) {
			cube.Render();
		}
	}
	OBJECTSHADER->UnUseProgram();
}
