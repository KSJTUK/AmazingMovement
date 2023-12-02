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
	std::pair<float, float> m_animationSpeedRange{ 1.f, 50.f };

	float m_sortTime{ };
	float m_timeCount{ };

	void(AnimationCubes::*m_sortFunc)(){ nullptr };
	bool m_sortEnd{ false };

	BubbleSortDT m_bubbleData{ };

private:
	void MakeCubes();

	bool CompareData(int32 idx1, int32 idx2);
	void SwapData(int32 idx1, int32 idx2);
	void SelectData(int32 idx1, int32 idx2);

	void StepSort();

	void SettingBeforeSort();

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