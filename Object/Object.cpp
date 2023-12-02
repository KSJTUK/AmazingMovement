#include "pch.h"
#include "Object.h"
#include "Model/ModelList.h"

Object::Object(const std::string& modelTag, const glm::vec3& color) : m_objectColor { color }{
	m_model = MODELLIST->GetModel(modelTag);
}

Object::~Object() { }

void Object::SetPosition(const glm::vec3& position) {
	m_position = position;
}

void Object::SetScale(const glm::vec3& scale) {
	m_scale = scale;
}

void Object::SetScaleY(const float& yScale) {
	m_scale.y = yScale;
}

void Object::PositionSwap(Object& other) {
	glm::vec3 temp{ };
	temp = other.m_position;
	other.m_position = m_position;
	m_position = temp;
}

void Object::ScaleSwap(Object& other) {
	glm::vec3 temp{ };
	temp = other.m_scale;
	other.m_scale = m_scale;
	m_scale = m_scale;
}

void Object::SetColor(const glm::vec3& color) {
	m_objectColor = color;
}

void Object::Select() {
	m_objectColor = glm::vec3{ 1.f, 0.f, 0.f };
}

glm::mat4 Object::CalcTransformMat() {
	glm::mat4 unit{ 1.f };
	glm::mat4 scale = glm::scale(unit, m_scale);
	glm::mat4 trans = glm::translate(unit, m_position);
	return trans * scale;
}
