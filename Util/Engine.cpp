#include "pch.h"
#include "Util/Engine.h"
#include "Util/callbacks.h"
#include "Util/Timer.h"
#include "Graphics/GameWorld.h"

Engine::Engine() {
	m_windowInfo = std::make_shared<WindowInfo>();

	m_windowInfo->x = 100;
	m_windowInfo->y = 100;
	m_windowInfo->width = 800;
	m_windowInfo->height = 600;
	m_windowInfo->fWidth = static_cast<float>(m_windowInfo->width);
	m_windowInfo->fHeight = static_cast<float>(m_windowInfo->height);

	std::string title{ "OpenGL Project 03" };
	std::string::size_type size = title.size();
	m_windowInfo->windowTitle = new char[size + 1] {};
	memcpy(m_windowInfo->windowTitle, title.c_str(), size + 1);
}

Engine::~Engine() {
	// 동적할당 객체들 메모리 할당 해제
	if (m_windowInfo->windowTitle) {
		delete[] m_windowInfo->windowTitle;
	}
}

// 콜백함수들 등록
void Engine::SubscribeCallbacks() {
	glutDisplayFunc(renderFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(specialkeyFunc);
	glutSpecialUpFunc(specialKeyUpFunc);
}

size_t Engine::GetWindowWidth() const {
	return m_windowInfo->width;
}

size_t Engine::GetWindowHeight() const {
	return m_windowInfo->height;
}

float Engine::GetWindowWidthF() const {
	return m_windowInfo->fWidth;
}

float Engine::GetWindowHeightF() const {
	return m_windowInfo->fHeight;
}

void Engine::SetWindowSize(int32 windowWidth, int32 windowHeight) {
	m_windowInfo->width = static_cast<size_t>(windowWidth);
	m_windowInfo->height = static_cast<size_t>(windowHeight);
	m_windowInfo->fWidth = static_cast<float>(windowWidth);
	m_windowInfo->fHeight = static_cast<float>(windowHeight);
}


void Engine::Init(int32* argc, char** argv) {
	// glut라이브러리 초기화
	glutInit(argc, argv);

	// 윈도우 출력모드 설정(더블버퍼링, RGBA, 깊이버퍼)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// 윈도우 크기, 좌표 설정
	glutInitWindowPosition(m_windowInfo->x, m_windowInfo->y);
	glutInitWindowSize(m_windowInfo->width, m_windowInfo->height);

	// 윈도우 생성
	glutCreateWindow(m_windowInfo->windowTitle);

	// glew 라이브러리 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw "GLEW 라이브러리 초기화 실패";
	}

	glEnable(GL_DEPTH_TEST);

	SubscribeCallbacks();

	//((bool(__stdcall*)(int))wglGetProcAddress("wglSwapIntervalEXT"))(0); // 수직 동기화

	// 타이머 초기화
	m_timer = std::make_unique<Timer>();
	m_timer->Init();

	m_grapics = std::make_unique<GameWorld>();
	m_grapics->SetWindowInfo(m_windowInfo);
	m_grapics->Init();
}

void Engine::ReSizeWindow(int32 w, int32 h) {
	m_windowInfo->width = w;
	m_windowInfo->height = h;
	m_windowInfo->fWidth = static_cast<float>(m_windowInfo->width);
	m_windowInfo->fHeight = static_cast<float>(m_windowInfo->height);

	if (m_grapics->IsInited()) {
		m_grapics->SetWindowInfo(m_windowInfo);
	}
}

void Engine::Update() {
	m_timer->Update();
	m_deltaTime = m_timer->GetDeltaTime();
	float fps = m_timer->GetFrame();
	//std::cout << m_deltaTime << "   " << fps << "\n";
	m_grapics->Update(m_deltaTime);
}

void Engine::Render() {
	m_grapics->Render();
}

void Engine::Input(unsigned char key, bool down) {
	m_grapics->Input(key, down);
}

void Engine::SpecialInput(int32 key, bool down) {
	m_grapics->SpecialInput(key, down);
}

void Engine::MouseMotionInput(int32 x, int32 y) {
	m_grapics->MouseMotionInput(x, y, m_mousePrevPos[0], m_mousePrevPos[1]);
	m_mousePrevPos[0] = x;
	m_mousePrevPos[1] = y;
}

void Engine::MousePassiveMotionInpit(int32 x, int32 y) {
	m_mousePrevPos[0] = x;
	m_mousePrevPos[1] = y;
}

void Engine::Loop() {
	glutMainLoop();
}

void Engine::LoopEnd() {
	glutLeaveMainLoop();
}
