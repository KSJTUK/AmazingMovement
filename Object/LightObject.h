#pragma once

#include "Object/Object.h"

struct LightOption {
	glm::vec3 position{ };
	glm::vec3 ambient{ 0.5f };
	glm::vec3 diffuse{ 0.5f };
	glm::vec3 specular{ 1.f };
};

class LightObject : public Object {
public:
	LightObject(const std::string& modelTag);
	LightObject(const std::string& modelTag, const glm::vec3& lightColor);
	virtual  ~LightObject();

	void DirLightOn();
	void DirLightOff();

private:
	LightOption m_lightOption{ };
	bool m_directionLightOn{ };
	bool m_spotLightOn{ };

public:
	void SetLightOption();

public:
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

