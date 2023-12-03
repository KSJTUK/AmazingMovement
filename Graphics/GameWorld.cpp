#include "pch.h"
#include "Graphics/GameWorld.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"

#include "Graphics/SkyBox.h"
#include "Graphics/Terrain.h"

#include "Model/ModelList.h"

#include "Object/AnimationCubes.h"
#include "Object/LightObject.h"

GameWorld::GameWorld() { }

GameWorld::~GameWorld() { }

bool GameWorld::IsInited() const {
	return m_isInited;
}

void GameWorld::SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo) {
	m_windowInfo = winInfo;
	CalcPerspectiveMat();
}

void GameWorld::CalcPerspectiveMat() {
	if (!m_isInited) {
		return;
	}

	float aspect = m_windowInfo->fWidth / m_windowInfo->fHeight;
	float halfFovy = m_fovy / 2.f;

	m_perspectiveMatrix = glm::perspective(glm::radians(halfFovy), aspect, m_near, m_far);
}

void GameWorld::CalcOrthoMat() {
	m_orthoMatrix = glm::ortho(0.0f, m_windowInfo->fWidth, 0.0f, m_windowInfo->fHeight, m_near, m_far);;
}

void GameWorld::Input(unsigned char key, bool down) {
	m_camera->Input(key, down);
	m_animationCubes->Input(key, down);
}

void GameWorld::SpecialInput(int key, bool down) {
	if (down) {
		if (key == GLUT_KEY_F3) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (key == GLUT_KEY_F4) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
}

void GameWorld::MouseMotionInput(int x, int y, int prevX, int prevY) {
	m_camera->MouseMotionInput(x, y, prevX, prevY);
}

void GameWorld::MousePassiveMotionInput(int x, int y, int prevX, int prevY) {
}

void GameWorld::CreateShaderPrograms() {
	OBJECTSHADER->CreateShaderProgram();
	LIGHTOBJECTSHADER->CreateShaderProgram();
	PARTICLESHADER->CreateShaderProgram();
	TERRAINSHADER->CreateShaderProgram();
	BACKGROUNDSHADER->CreateShaderProgram();
}

void GameWorld::SetPerspectiveAllShader() {
	BACKGROUNDSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
	TERRAINSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
	PARTICLESHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
	OBJECTSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
	LIGHTOBJECTSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
}

void GameWorld::SetOrthoAllShader() {
	BACKGROUNDSHADER->SetUniformMat4("perspective", m_orthoMatrix);
	TERRAINSHADER->SetUniformMat4("perspective", m_orthoMatrix);
	PARTICLESHADER->SetUniformMat4("perspective", m_orthoMatrix);
	OBJECTSHADER->SetUniformMat4("perspective", m_orthoMatrix);
	LIGHTOBJECTSHADER->SetUniformMat4("perspective", m_orthoMatrix);
}

void GameWorld::SetViewMatAllShader(const glm::mat4& viewMat) {
	BACKGROUNDSHADER->SetUniformMat4("view", glm::mat4(glm::mat3(viewMat)));
	TERRAINSHADER->SetUniformMat4("view", viewMat);
	PARTICLESHADER->SetUniformMat4("view", viewMat);
	OBJECTSHADER->SetUniformMat4("view", viewMat);
	LIGHTOBJECTSHADER->SetUniformMat4("view", viewMat);
}

void GameWorld::InitModelList() {
	// 모델리스트를 생성하고 모델 불러오기
	OBJECTSHADER->UseProgram();
	MODELLIST->Init();
	MODELLIST->LoadModel("cube.obj");
	MODELLIST->LoadModel("sphere.obj");
	OBJECTSHADER->UnUseProgram();
}

void GameWorld::SetGLGraphicOptions() {
	glPointSize(2.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GameWorld::WorldRender() {
	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);

	m_camera->Render();
	SetPerspectiveAllShader();
	SetViewMatAllShader(m_camera->GetViewMat());;

	m_background->Render();

	m_light->Render();
	//m_ground->Render();

	m_animationCubes->Render();
}

void GameWorld::MinimapRender() {
	int minimapWidth = m_windowInfo->width / 4;
	int minimapHeight = m_windowInfo->height / 4;
	glViewport((m_windowInfo->width) - minimapWidth, (m_windowInfo->height) - minimapHeight, minimapWidth, minimapHeight);

	m_minimapCamera->Render();

	SetOrthoAllShader();
	SetViewMatAllShader(m_minimapCamera->GetViewMat());

	m_background->Render();

	m_light->Render();
	//m_ground->Render();
	m_animationCubes->Render();
}

void GameWorld::GenerateAnimationCube() {
	int w{ }, h{ };
	while (true) {
		std::cout << "가로와 세로를 입력해주세요 크기제한은 30입니다" << std::endl;
		std::cout << "30을 넘어서는 크기를 입력하면 크기가 30으로 고정됩니다." << std::endl;
		std::cin >> w;
		if (!std::cin) {
			std::cout << "다시 입력해주세여" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

		std::cin >> h;
		if (!std::cin) {
			std::cout << "다시 입력해주세여" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}


		break;
	}

	w = static_cast<int>(w);
	w = static_cast<int>(h);
	std::clamp(w, 0, 30);
	std::clamp(h, 0, 30);

	m_animationCubes = std::make_unique<AnimationCubes>(500.f, glm::uvec2{ w, h });
	m_animationCubes->PrintKeyInfo();
}

void GameWorld::Init() {
	CreateShaderPrograms();
	SetGLGraphicOptions();

	InitModelList();

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_minimapCamera = std::make_unique<Camera>();
	m_minimapCamera->CameraPositionSet(glm::vec3{ 0.f, 500.f, 800.f });
	m_minimapCamera->CameraViewPointSet(glm::vec3{ 0.f, -0.5f, -1.f });

	// SkyBox 생성
	m_background = std::make_unique<SkyBox>();
	//m_ground = std::make_unique<Terrain>(glm::uvec2{ 20, 20 });

	// 테스트용 큐브 생성

	m_light = std::make_unique<LightObject>("sphere", glm::vec3{ 1.f, 1.f, 1.f });
	m_light->SetPosition(glm::vec3{ 0.f, 100.f, 30.f });
	m_light->SetScale(glm::vec3{ 0.1f });

	m_light->DirLightOn();

	InitModelList();

	// 투영 변환 행렬 계산
	CalcPerspectiveMat();

	m_isInited = true;
	GenerateAnimationCube();
}

void GameWorld::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);
	m_minimapCamera->Update(m_deltaTime);

	m_animationCubes->Update(m_deltaTime);
}

void GameWorld::Render() {
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	WorldRender();

	MinimapRender();

	glutSwapBuffers();
}