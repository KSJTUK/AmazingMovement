#pragma once

struct BubbleSortDT {
	int32 selectIdx{ 1 };
	int32 targetIdx{ };
};

struct SelectionSortDT { 
	int32 selectIdx{ };
	int32 targetIdx{ };
};

struct InsertionSortDT {
	int32 selectIdx{ 1 };
	int32 targetIdx{ };
};

struct QuickSortDT {
	int32 left{ };
	int32 right{ };
	// 재귀 없이 구현하기위해 배열 스택 사용
	int32 stackTop{ -1 };
	int32 lStack[200]{ };
	int32 rStack[200]{ };

	bool partitionEnd{ true };

	int32 pivot{ };
	int32 topLeft{ };
	int32 topRight{ };
	int32 popData{ -1 };

	int32 targetLeft{ };
	int32 targetRight{ };

	bool selectedLeft{ };
	bool selectedRight{ };
	bool selectFailLeft{ };
	bool selectFailRight{ };
};

enum class ANIMATION_ENUM {
	BUBBLE_SORT,
	QUICK_SORT
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

	bool m_animationOn{ };
	bool m_inSortAnimation{ };
	bool m_startSort{ };

	float m_sortTime{ 0.3f };
	float m_timeCount{ };

	const int m_numSortData{ 100 };
	void(AnimationCubes::*m_sortFunc)(){ nullptr };
	bool m_sortEnd{ false };

	BubbleSortDT m_bubbleData{ };
	QuickSortDT m_qSortData{ 0, m_numSortData - 1, -1, { }, true };
	InsertionSortDT m_insertionData{ };
	SelectionSortDT m_selectionData{ };

	int m_sorting{ 0 };

private:
	void MakeCubes();

	// 모든 sort 함수들이 사용할 함수들
	// ----------------------------------
	void MakeSortCubes();

	void SuffleData();
	void ResetColor();
	bool CompareData(int32 idx1, int32 idx2);
	void SwapData(int32 idx1, int32 idx2);
	void SelectData(int32 idx1, int32 idx2);

	void StepSort();

	void SettingBeforeSort();
	// ----------------------------------
	void QuickSortInit();
	void QuickSortPartition();

public:
	void SetScaleRange(const float& min, const float& max);
	void SetRandomScaleAnimation();
	void SetWaveAnimation();

	void SetSortAnimation();
	void BubbleSort();
	void InsertionSort();
	void SelectionSort();
	void MergeSort();
	void QuickSort();

	void PrintKeyInfo();

public:
	void Input(unsigned char key, bool down);
	void Update(float deltaTime);
	void Render();
};