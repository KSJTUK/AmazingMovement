#pragma once

class AnimationCubes {
public:
	AnimationCubes(const float xzMapSize, const glm::uvec2& numOfCubes);
	~AnimationCubes();

private:
	std::vector<std::vector<class Cube>> m_cubes{ };

	float m_mapSize{ };
	glm::uvec2 m_numCubes{ };

	std::pair<float, float> m_scaleRange{ 0.1f, 50.f };
	std::pair<float, float> m_animationSpeedRange{ 1.f, 30.f };

public:
	void SetScaleRange(const float& min, const float& max);

public:
	void Update(float deltaTime);
	void Render();
};