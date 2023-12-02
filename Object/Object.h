#pragma once

class Object {
public:
	Object(const std::string& modelTag, const glm::vec3& color);
	virtual ~Object();

protected:
	std::shared_ptr<class Model> m_model{ };
	//std::unique_ptr<class TextureComponent> m_texture{ nullptr };


	glm::vec3 m_position{ };
	glm::vec3 m_scale{ 1.f };
	glm::vec3 m_rotate{ };
	glm::vec3 m_objectColor{ };

	Meterial m_meterial{ };

public:
	void SetPosition(const glm::vec3& position);
	void SetScale(const glm::vec3& scale);
	void SetScaleY(const float& yScale);
	void PositionSwap(Object& other);
	void ScaleSwap(Object& other);
	void SetColor(const glm::vec3& color);

	void Select();

	glm::mat4 CalcTransformMat();

public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

};

