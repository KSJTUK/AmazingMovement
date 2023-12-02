#pragma once
#include "Object/Object.h"

class Cube : public Object {
public:
	Cube(const glm::vec3& color);
	Cube(const glm::vec3& color, const glm::vec3& position, const glm::vec3& scale);
	virtual ~Cube();

private:
	const std::string m_modelTag{ "cube" };

	float m_deltaTime{ };

	std::pair<float, float> m_scaleAnimationRange{ 1.f, 50.f };
	std::pair<float, float> m_xzScale{ };

	float m_scaleAnimationSpeed{ 10.f };
	float m_scaleDirection{ 1.f };
	
public:
	void SetAnimationOption(const std::pair<float, float>& animationRange, const float& speed);
	void ScaleAnimation();
	void SetAnimationSpeed(const float& speed);

public:
	void SetMeterials(const Meterial& meterial);
	void Setambient(const glm::vec3& ambient);
	void SetDiffuse(const glm::vec3& deffuse);
	void SetSpecular(const glm::vec3& specular);
	void SetShininess(const float& shininess);

public:
	void SetUniformMeterials();

	glm::vec3 GetScale() { return m_scale; }
	float GetScaleY() { return m_scale.y; }

public:
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

