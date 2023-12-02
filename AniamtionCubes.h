#pragma once

class AnimationCubes {
public:
	AnimationCubes(float cubeXZSize, const float xzMapSize, const glm::uvec2& numOfCubes);
	~AnimationCubes();

private:
	//std::vector<std::vector<class Cube>> m_cubes{ };

	float m_xzSize{ };
	float m_mapSize{ };
	glm::uvec2 m_numCubes{ };

	std::pair<float, float> m_scaleRange{ };

public:
	void SetScaleRange(const float& min, const float& max);

public:
	void Update(float deltaTime);
	void Render();
};