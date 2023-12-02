#include "pch.h"
#include "Graphics/Shader.h"
#include "Model/Model.h"
#include "Cube.h"

Cube::Cube(const std::string modelTag, const glm::vec3& color) : Object{ modelTag, color } { }

Cube::~Cube() { }

void Cube::SetUniformMeterials() {
	OBJECTSHADER->SetUniformInt("meterials.diffuse", 0);
	OBJECTSHADER->SetUniformVec3("meterials.specular", m_meterial.specular);
	OBJECTSHADER->SetUniformFloat("meterials.shininess", m_meterial.shininess);
}

void Cube::Update(float deltaTime) {

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
