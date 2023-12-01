#pragma once

class GameWorld {
public:
	GameWorld();
	~GameWorld();

private:
	bool m_isInited{ false };
	std::unique_ptr<class Camera> m_camera{ };

private:
	// 카메라 외부파라미터 (투영행렬을 생성할 떄 쓰일 변수들)
	float m_fovy{ 90.f }; // 수직 시야각

	// 스크린 화면의 크기를 알아내기 위한 WindowInfo객체 참조
	std::shared_ptr<struct WindowInfo> m_windowInfo{ }; // aspect(종횡비) = width / height
	std::unique_ptr<class SkyBox> m_background{ }; // SkyBox 배경
	std::unique_ptr<class Terrain> m_ground{ };

	float m_near{ 0.1f };           // 시야 절두체의 가까운 평면과의 거리
	float m_far{ 10000.f };           // 시야 절두체의 먼 평면과의 거리

	glm::mat4 m_perspectiveMatrix{ 1.f };

	float m_deltaTime{ };

public:
	// getter
	bool IsInited() const;

	// setter
	void SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo);
	void CalcPerspectiveMat();

public:
	// 외부 키입력을 카메라에게 전해주는 함수
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void MouseMotionInput(int x, int y, int prevX, int prevY);
	void MousePassiveMotionInput(int x, int y, int prevX, int prevY);

	void CreateShaderPrograms();
	void SetPerspectiveAllShader();
	void SetViewMatAllShader();
	void InitModelList();
	void SetGLGraphicOptions();

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

