#pragma once

class Camera {
public:
	Camera() { }
	~Camera() { }

private:
	// 카메라의 내부 파라미터
	glm::vec3 m_EYE{ 0.f, 0.f, 3.f };
	glm::vec3 m_AT{ 0.f, 0.f, -1.f };
	glm::vec3 m_UP{ 0.f, 1.f, 0.f };

	// 뷰변환 행렬
	glm::mat4 m_view{ 1.f };

	// 카메라 업데이트를 위한 시간 값 저장
	float m_deltaTime{ };

	// 카메라 움직임을 위한 변수들
	float m_moveSpeed{ 100.f };
	float m_angleSpeed{ 3.f };

	float m_fixAt{ 1.f };

	// 카메라가 가지는 기저, 카메라의 축 방향 벡터들을 저장할 변수
	glm::vec3 m_cameraAxisX{ };
	glm::vec3 m_cameraAxisY{ };
	glm::vec3 m_cameraAxisZ{ };

	float m_cameraAngleX{ };
	float m_cameraAngleY{ };

	int m_rotateY{ 0 };
	int m_orbitY{ 0 };

	bool m_spotLightingOn{ false };

public:
	// getter
	const glm::mat4& GetViewMat() const;

	// setter
	void CameraPositionSet(const glm::vec3& position);
	void CameraViewPointSet(const glm::vec3& at);
	void CameraMoveSpeedSet(const float& speed);

	float GetCameraAngleX() const { return m_cameraAngleX; }
	float GetCameraAngleY() const { return m_cameraAngleY; }

	void ViewPointFix();
	void ViewPointUnFix();

	void CameraPositionRotateX(const float& angle, const glm::vec3& center);

public:
	// 외부 키입력을 카메라가 자체적으로 처리하게 함
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void MouseMotionInput(int x, int y, int prevX, int prevY);
	void MousePassiveMotionInput(int x, int y, int prevX, int prevY);

	void Move(const glm::vec3& moveVec);
	void ViewPointMove(float moveAngle, const glm::vec3& axis);

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

