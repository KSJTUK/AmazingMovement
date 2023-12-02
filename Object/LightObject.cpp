#include "pch.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "LightObject.h"

LightObject::LightObject(const std::string& modelTag) : Object{ modelTag, glm::vec3{ 1.f } } { }

LightObject::LightObject(const std::string& modelTag, const glm::vec3& lightColor) : Object{ modelTag, lightColor } { }

LightObject::~LightObject() { }

void LightObject::DirLightOn() {
	m_directionLightOn = true;
}

void LightObject::DirLightOff() {
	m_directionLightOn = false;
}

void LightObject::SetLightOption() {
	glm::vec3 diffuseColor{ m_objectColor * m_lightOption.diffuse };
	glm::vec3 ambientColor{ diffuseColor * m_lightOption.ambient };
	m_lightOption.specular = m_objectColor;

	// phong, point lighting
	m_lightOption.position = m_position;
	OBJECTSHADER->SetUniformVec3("pointLight.position", m_lightOption.position);

	// Direction Lighting
	if (m_directionLightOn) {
		OBJECTSHADER->SetUniformVec3("dirLight.direction", glm::vec3{ 0.f, -1.f, 0.f });
		OBJECTSHADER->SetUniformVec3("dirLight.ambient", ambientColor);
		OBJECTSHADER->SetUniformVec3("dirLight.diffuse", diffuseColor);
		OBJECTSHADER->SetUniformVec3("dirLight.specular", glm::vec3{ 0.f });
	}

	//point, flash lightting
	OBJECTSHADER->SetUniformVec3("pointLight.ambient", ambientColor);
	OBJECTSHADER->SetUniformVec3("pointLight.diffuse", diffuseColor);
	OBJECTSHADER->SetUniformVec3("pointLight.specular", m_lightOption.specular);

	OBJECTSHADER->SetUniformFloat("pointLight.constant", 1.0f);
	OBJECTSHADER->SetUniformFloat("pointLight.linear", 0.00014f);
	OBJECTSHADER->SetUniformFloat("pointLight.quadratic", 0.000007f);

	if (m_spotLightOn) {
		OBJECTSHADER->SetUniformVec3("spotLight.ambient", ambientColor);
		OBJECTSHADER->SetUniformVec3("spotLight.diffuse", diffuseColor);
		OBJECTSHADER->SetUniformVec3("spotLight.specular", m_lightOption.specular);

		OBJECTSHADER->SetUniformFloat("spotLight.constant", 1.0f);
		OBJECTSHADER->SetUniformFloat("spotLight.linear", 0.027f);
		OBJECTSHADER->SetUniformFloat("spotLight.quadratic", 0.0028f);
	}
}

void LightObject::Update(float deltaTime) {
}

void LightObject::Render() {
	SetLightOption();

	LIGHTOBJECTSHADER->SetUniformVec3("objectColor", m_objectColor);

	LIGHTOBJECTSHADER->SetUniformMat4("transform", CalcTransformMat());

	LIGHTOBJECTSHADER->UseProgram();
	m_model->Render();
	LIGHTOBJECTSHADER->UseProgram();
}
