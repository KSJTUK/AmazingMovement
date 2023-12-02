#include "pch.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Cube.h"

Cube::Cube(const glm::vec3& color) : Object{ "cube", color } { }

Cube::~Cube() { }

void Cube::SetAnimationOption(const std::pair<float, float>& animationRange) {
	m_scaleAnimationRange = animationRange;
}

void Cube::ScaleAnimation() {
	if (m_scale.y > m_scaleAnimationRange.second) {
		m_scale.y = m_scaleAnimationRange.second;
		m_scaleDirection = -1.f;
	}
	else if (m_scale.y < m_scaleAnimationRange.first) {
		m_scale.y = m_scaleAnimationRange.first;
		m_scaleDirection = 1.f;
	}
	
	m_scale.y += m_scaleDirection * m_scaleAnimationSpeed * m_deltaTime;
}

void Cube::SetUniformMeterials() {
	OBJECTSHADER->SetUniformInt("meterials.diffuse", 0);
	OBJECTSHADER->SetUniformVec3("meterials.specular", m_meterial.specular);
	OBJECTSHADER->SetUniformFloat("meterials.shininess", m_meterial.shininess);
}

void Cube::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	ScaleAnimation();
}

void Cube::Render() { 
	SetUniformMeterials();
	OBJECTSHADER->SetUniformVec3("objectColor", m_objectColor);
	OBJECTSHADER->SetUniformMat4("transform", CalcTransformMat());

	if (m_model->ExistTexture()) {
		OBJECTSHADER->SetUniformBool("notextureID", false);
	}
	else {
		OBJECTSHADER->SetUniformBool("notextureID", true);
	}

	OBJECTSHADER->UseProgram();

	m_model->Render();

	OBJECTSHADER->UnUseProgram();
}
