#include "pch.h"
#include "Graphics/GameWorld.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Model/ModelList.h"

#include "Util/TextureComponent.h"

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

void GameWorld::Input(unsigned char key, bool down) {
	m_camera->Input(key, down);
}

void GameWorld::SpecialInput(int key, bool down) {
	if (down) {
		if (key == GLUT_KEY_F1) {
			OBJECTSHADER->UseProgram();
			OBJECTSHADER->UnUseProgram();
		}

		if (key == GLUT_KEY_F2) {
			OBJECTSHADER->UseProgram();
			OBJECTSHADER->UnUseProgram();
		}

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
	BACKGROUNDSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	TERRAINSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	PARTICLESHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	OBJECTSHADER->SetUniformMat4("perspectiveMat", m_perspectiveMatrix);
	LIGHTOBJECTSHADER->SetUniformMat4("perspective", m_perspectiveMatrix);
}

void GameWorld::SetViewMatAllShader() {
	glm::mat4 cameraViewMatrix{ m_camera->GetViewMat() };

	BACKGROUNDSHADER->SetUniformMat4("viewMat", glm::mat4(glm::mat3(cameraViewMatrix)));
	TERRAINSHADER->SetUniformMat4("viewMat", cameraViewMatrix);
	PARTICLESHADER->SetUniformMat4("viewMat", cameraViewMatrix);
	OBJECTSHADER->SetUniformMat4("viewMat", cameraViewMatrix);
	LIGHTOBJECTSHADER->SetUniformMat4("view", cameraViewMatrix);
}

void GameWorld::InitModelList() {
	// 모델리스트를 생성하고 모델 불러오기
	MODELLIST->Init();
	MODELLIST->LoadModel("cube.obj");
	//MODELLIST->LoadModel("cone.obj");
	//MODELLIST->LoadModel("sphere.obj");
	//MODELLIST->LoadModel("cylinder.obj");
	//MODELLIST->LoadModel("earth.obj", "Earth_diffuse_512p.png");
}

void GameWorld::SetGLGraphicOptions() {
	glPointSize(2.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void GameWorld::Init() {
	SetGLGraphicOptions();

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	InitModelList();

	// 투영 변환 행렬 계산
	CalcPerspectiveMat();

	m_isInited = true;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GameWorld::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);
}

void GameWorld::Render() {

	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	m_camera->Render();
	SetPerspectiveAllShader();
	SetViewMatAllShader();

	glViewport(0, 0, m_windowInfo->width, m_windowInfo->height);

	glutSwapBuffers();
}