#pragma once

class RandomEngine {
public:
	RandomEngine();
	~RandomEngine();

private:
	std::random_device m_rd{ };
	std::default_random_engine m_dre{ m_rd() };

public:
	int GetRandInt(int min, int max);
	float GetRandFloat(float min, float max);
	glm::vec2 GetRandVec2(const glm::vec2& min, const glm::vec2& max);
	glm::vec3 GetRandVec3(const glm::vec3& min, const glm::vec3& max);
	glm::vec4 GetRandVec4(const glm::vec4& min, const glm::vec4& max);

};

