#include "pch.h"
#include "AnimationCubes.h"
#include "Object/Cube.h"
#include "Graphics/Shader.h"
#include "Util/RandomEngine.h"

AnimationCubes::AnimationCubes(const float xzMapSize, const glm::uvec2& numOfCubes) : m_mapSize{ xzMapSize }, m_numCubes{ numOfCubes } {
	MakeCubes();

	SetRandomScaleAnimation();
	/*SetWaveAnimation();*/
	//SettingBeforeSort();
}

AnimationCubes::~AnimationCubes() { }

void AnimationCubes::MakeCubes() {
	glm::vec3 initColor{ 0.f, 1.f, 0.f };
	m_cubes.resize(m_numCubes.y);

	float width = m_mapSize / (m_numCubes.x);
	float height = m_mapSize / (m_numCubes.y);
	// 카메라 기준 왼쪽 위
	glm::vec2 leftTop{ -width * (m_numCubes.x / 2.f), -height * (m_numCubes.y / 2.f) };

	float scaleStep = m_scaleRange.second / (m_numCubes.y + 2);

	for (uint32 z = 0; z < m_numCubes.y; ++z) {
		for (uint32 x = 0; x < m_numCubes.x; ++x) {
			glm::vec3 scale{ width, 1.f, height };
			glm::vec3 position{ leftTop.x + width * x, 0.f, leftTop.y + height * z };
			m_cubes[z].emplace_back(initColor, position, scale);
		}
	}
}

bool AnimationCubes::CompareData(int32 idx1, int32 idx2) {
	if (m_cubes[0][idx1].GetScaleY() >= m_cubes[0][idx2].GetScaleY()) {
		return true;
	}
	return false;
}

void AnimationCubes::SwapData(int32 idx1, int32 idx2) {
	for (int z = 0; z < m_numCubes.y; ++z) {
		glm::vec3 leftScale{ m_cubes[z][idx1].GetScale() };
		glm::vec3 rightScale{ m_cubes[z][idx2].GetScale() };
		m_cubes[z][idx2].SetScale(leftScale);
		m_cubes[z][idx1].SetScale(rightScale);
	}
}

void AnimationCubes::SelectData(int32 idx1, int32 idx2) {
	for (int z = 0; z < m_numCubes.y; ++z) {
		m_cubes[z][idx1].Select();
		m_cubes[z][idx2].Select();
	}
}

void AnimationCubes::StepSort() {
	if (!m_sortFunc) return;

	BubbleSort();
	
	m_timeCount += m_deltaTime;
}

void AnimationCubes::SettingBeforeSort() {
	float scaleStep = m_scaleRange.second / (m_numCubes.y + 2);
	for (uint32 z = 0; z < m_numCubes.y; ++z) {
		for (uint32 x = 0; x < m_numCubes.x; ++x) {
			m_cubes[z][x].SetScaleY(scaleStep * x);
		}
	}
}

void AnimationCubes::SetScaleRange(const float& min, const float& max) {
	m_scaleRange = { min, max };
}

void AnimationCubes::SetRandomScaleAnimation() {
	for (uint32 z = 0; z < m_numCubes.y; ++z) {
		for (uint32 x = 0; x < m_numCubes.x; ++x) {
			float randomYScale = randomEngine->GetRandFloat(m_scaleRange.first, m_scaleRange.second);
			float randomSpeed = randomEngine->GetRandFloat(m_animationSpeedRange.first, m_animationSpeedRange.second);
			float yScale{ randomYScale };

			m_cubes[z][x].SetScaleY(randomYScale);
			m_cubes[z][x].SetAnimationOption(m_scaleRange, randomSpeed);
		}
	}
}

void AnimationCubes::SetWaveAnimation() {
	float scaleStep = m_scaleRange.second / (m_numCubes.y + 2);
	for (uint32 z = 0; z < m_numCubes.y; ++z) {
		for (uint32 x = 0; x < m_numCubes.x; ++x) {
			m_cubes[z][x].SetScaleY(scaleStep * x);
			m_cubes[z][x].SetAnimationOption(m_scaleRange, m_waveSpeed);
		}
	}
}

void AnimationCubes::SetSortAnimation() {

}

void AnimationCubes::BubbleSort() {
	if (m_bubbleData.targetIdx >= m_bubbleData.selectIdx) {
		m_bubbleData.selectIdx += 1;
		if (m_bubbleData.selectIdx >= m_numCubes.x) {
			m_sortEnd = true;
			return;
		}

		m_bubbleData.targetIdx = 0;
		SelectData(m_bubbleData.selectIdx, m_bubbleData.targetIdx);
		return;
	}


	if (CompareData(m_bubbleData.targetIdx, m_bubbleData.selectIdx)) {
		SwapData(m_bubbleData.targetIdx, m_bubbleData.selectIdx);
	}
}

void AnimationCubes::Update(float deltaTime) {
	m_deltaTime = deltaTime;

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
