#pragma once

class Engine {
public:
	// 기본 생성, 소멸자
	Engine();
	~Engine();

	// 객체의 복사를 금지
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

private:
	std::shared_ptr<WindowInfo> m_windowInfo{ };

	std::unique_ptr<class Timer> m_timer{ nullptr };
	std::unique_ptr<class GameWorld> m_grapics{ nullptr };

	int32 m_mousePrevPos[2]{ };

	float m_deltaTime{ };

private:
	// 멤버함수 내에서만 쓰일 함수들 정의
	void SubscribeCallbacks();

public:
	size_t GetWindowWidth() const;
	size_t GetWindowHeight() const;
	float GetWindowWidthF() const;
	float GetWindowHeightF() const;

	float GetDeltaTime() const { return m_deltaTime; };

	void SetWindowSize(int32 windowWidth, int32 windowHeight);

public:
	// 기본 멤버 객체들 생성, 윈도우 생성, 콜백함수 설정등을 하는 함수
	void Init(int32*, char**);

	// reshape콜백 함수가 불려올때 윈도우 크기를 변경할 함수
	void ReSizeWindow(int32, int32);

	// 게임 로직 업데이트 함수
	void Update();

	// 렌더링 명령 함수
	void Render();

	// 키 입력을 내부적으로 처리할 함수
	void Input(unsigned char key, bool down);
	void SpecialInput(int32 key, bool down);
	void MouseMotionInput(int32 x, int32 y);
	void MousePassiveMotionInpit(int32 x, int32 y);

	// 게임 루프함수
	void Loop();
	// 게임 종료함수
	void LoopEnd();
};