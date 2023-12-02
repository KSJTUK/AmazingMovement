#pragma once

struct BubbleSortDT {
	int32 selectIdx{ };
	int32 targetIdx{ };
};

struct SelectionSortDT{ 
	int32 selectIdx{ };
	int32 targetIdx{ };
};

class AnimationCubes {
public:
	AnimationCubes(const float xzMapSize, const glm::uvec2& numOfCubes);
	~AnimationCubes();

private:
	float m_deltaTime{ };

	std::vector<std::vector<class Cube>> m_cubes{ };

	float m_mapSize{ };
	glm::uvec2 m_numCubes{ };

	float m_waveSpeed{ 30.f };

	std::pair<float, float> m_scaleRange{ 0.1f, 50.f };
	std::pair<float, float> m_animationSpeedRange{ 1.f, 30.f };

	float m_sortTime{ };
	float m_timeCount{ };

	void(AnimationCubes::*m_sortFunc)(){ nullptr };

private:
	void StepSort();

public:
	void SetScaleRange(const float& min, const float& max);
	void SetRandomScaleAnimation();
	void SetWaveAnimation();

	void SetSortAnimation();
	void BubbleSort();

public:
	void Update(float deltaTime);
	void Render();
};