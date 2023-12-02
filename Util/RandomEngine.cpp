#include "pch.h"
#include "RandomEngine.h"

RandomEngine::RandomEngine() { }

RandomEngine::~RandomEngine() { }

int RandomEngine::GetRandInt(int min, int max) {
	std::uniform_int_distribution<> uid{ min, max };
	return uid(m_dre);
}

float RandomEngine::GetRandFloat(float min, float max) {
	std::uniform_real_distribution<> urd{ min, max };
	return static_cast<float>(urd(m_dre));
}

glm::vec2 RandomEngine::GetRandVec2(const glm::vec2& min, const glm::vec2& max) {
	return glm::vec2{ GetRandFloat(min.x, max.x), GetRandFloat(min.y, max.y) };
}

glm::vec3 RandomEngine::GetRandVec3(const glm::vec3& min, const glm::vec3& max) {
	return glm::vec3{ GetRandFloat(min.x, max.x), GetRandFloat(min.y, max.y), GetRandFloat(min.z, max.z) };
}

glm::vec4 RandomEngine::GetRandVec4(const glm::vec4& min, const glm::vec4& max) {
	return glm::vec4{ GetRandFloat(min.x, max.x), GetRandFloat(min.y, max.y), GetRandFloat(min.z, max.z), GetRandFloat(min.w, max.w)};
}
