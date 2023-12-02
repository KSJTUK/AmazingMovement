#pragma once

class AnimationCubes {
public:
	AnimationCubes(float cubeXZSize, const float xzMapSize, const glm::uvec2& numOfCubes);
	~AnimationCubes();

private:
	std::vector<std::vector<class Cube>> m_cubes{ };

public:
};