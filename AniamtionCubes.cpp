#include "pch.h"
#include "AniamtionCubes.h"

AnimationCubes::AnimationCubes(float cubeXZSize, const float xzMapSize, const glm::uvec2& numOfCubes) : m_xzSize{ cubeXZSize }, m_mapSize{ xzMapSize }, m_numCubes{ numOfCubes } {
	for (uint32 z = 0; z < m_numCubes.y; ++z) {
		for (uint32 x = 0; x < m_numCubes.x; ++x) {

		}
	}
}

AnimationCubes::~AnimationCubes() { }

void AnimationCubes::SetScaleRange(const float& min, const float& max) {
	m_scaleRange = { min, max };
}

void AnimationCubes::Update(float deltaTime) {
}

void AnimationCubes::Render() {

}
