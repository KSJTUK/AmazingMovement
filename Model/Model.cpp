#include "pch.h"
#include "Model/Model.h"
#include "Graphics/GraphicBuffers.h"
#include "Graphics/Shader.h"
#include "Util/TextureComponent.h"

Model::Model(const std::string& objectFilePath) {
	ReadObject(objectFilePath.c_str());
	m_textureComponent = nullptr;
}

Model::Model(const std::string& objectFilePath, const std::string& textureFilePath) {
	ReadObject(objectFilePath.c_str());
	m_textureComponent = std::make_unique<TextureComponent>();
	m_textureComponent->LoadTexture(textureFilePath, true);
}

Model::~Model() { }

void Model::CalcMinMaxVertexElem() {
	auto minAndMaxX = std::minmax_element(m_noDuplicatedVertex.begin(), m_noDuplicatedVertex.end(),
		[](const glm::vec3& v1, const glm::vec3& v2) {
			return v1.x < v2.x;
		}
	);

	auto minAndMaxY = std::minmax_element(m_noDuplicatedVertex.begin(), m_noDuplicatedVertex.end(),
		[](const glm::vec3& v1, const glm::vec3& v2) {
			return v1.y < v2.y;
		}
	);

	auto minAndMaxZ = std::minmax_element(m_noDuplicatedVertex.begin(), m_noDuplicatedVertex.end(),
		[](const glm::vec3& v1, const glm::vec3& v2) {
			return v1.z < v2.z;
		}
	);

	m_maxCoord = glm::vec3{ minAndMaxX.second->x, minAndMaxY.second->y, minAndMaxZ.second->z };
	m_minCoord = glm::vec3{ minAndMaxX.first->x, minAndMaxY.first->y, minAndMaxZ.first->z };
}

void Model::MakeBoundingBox() {
	m_boundingBox = { m_maxCoord, m_minCoord };
}

Vertex Model::GetMid(const Vertex& a, const Vertex& b) {
	Vertex mid = {
		(a.position + b.position) / 2.f,
		a.texture,
		a.normal
	};
	return mid;
}

void Model::CreateSierpinski(const int& level, int recursionDepth) {
	if (level == ++recursionDepth) {
		return;
	}

	std::vector<Vertex> tempVertex{ };

	int triangleSize = 3;
	size_t loopSize = m_verticies.size();
	for (int i = 0; i < loopSize; i += triangleSize) {
		Vertex mid1 = GetMid(m_verticies[i], m_verticies[i + 1]);
		Vertex mid2 = GetMid(m_verticies[i + 1], m_verticies[i + 2]);
		Vertex mid3 = GetMid(m_verticies[i + 2], m_verticies[i]);

		tempVertex.push_back(m_verticies[i]); // triangle 1
		tempVertex.push_back(mid1);
		tempVertex.push_back(mid3);

		tempVertex.push_back(mid1);          // triangle 2
		tempVertex.push_back(m_verticies[i + 1]);
		tempVertex.push_back(mid2);

		tempVertex.push_back(mid3);           // triangle 3
		tempVertex.push_back(mid2);
		tempVertex.push_back(m_verticies[i + 2]);
	}

	m_verticies.swap(tempVertex);
	//std::copy(tempVertex.begin(), tempVertex.end(), m_verticies.begin());

	Model::CreateSierpinski(level, recursionDepth);
}

void Model::ReadFace(std::stringstream& contents, std::vector<unsigned int>* indiciesVec) {
	std::string delTag{ };
	std::string face[3]{ };        // f a/b/c -> a == ���� �ε���, b == �ؽ�ó �ε���, c == ��� �ε���
	contents >> delTag >> face[0] >> face[1] >> face[2];

	for (int i = 0; i < 3; ++i) {
		std::string temp{ };
		int cnt{ };
		int faceSize{ static_cast<int>(face[i].size()) };
		for (int c = 0; faceSize; ++c) {
			if (face[i][c] == '\0') {
				indiciesVec[cnt].push_back(std::stoi(temp) - 1);
				break;
			}

			if (face[i][c] == '/') {
				if (!temp.empty()) {
					indiciesVec[cnt].push_back(std::stoi(temp) - 1);
				}
				cnt++;
				temp.clear();
			}
			else {
				temp += face[i][c];
			}
		}
	}
}

void Model::ReadVertex(std::stringstream& contents, std::vector<glm::vec3>& positions) {
	std::string delTag{ };
	glm::vec3 tempVec{ };      // ���� ��ǥ ����
	contents >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
	positions.push_back(tempVec);
}

void Model::ReadVertexTexture(std::stringstream& contents, std::vector<glm::vec2>& textureCoords) {
	std::string delTag{ };
	glm::vec2 tempVec{ };      // ���� ��ǥ ����
	contents >> delTag >> tempVec.x >> tempVec.y;
	textureCoords.push_back(tempVec);
}

void Model::ReadVertexNormal(std::stringstream& contents, std::vector<glm::vec3>& normals) {
	std::string delTag{ };
	glm::vec3 tempVec{ };      // ���� ��ǥ ����
	contents >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
	normals.push_back(tempVec);
}

void Model::ReadObject(const char* filePath) {
	std::ifstream objFile{ filePath, std::ios::in };

	std::vector<unsigned int> indiciesVec[3]{ }; // cnt: 0 == vertex, 1 == texture, 2 == nomal

	std::vector<glm::vec3> vertexPositions{ };
	std::vector<glm::vec2> vertexTextureCoord{ };
	std::vector<glm::vec3> vertexNormals{ };

	if (!objFile.is_open()) {
		assert(0);
	}

	std::string line{ "" };
	while (!objFile.eof()) {
		std::getline(objFile, line);
		std::stringstream sstream{ line };
		std::string delTag{ };     // �տ� �ִ� v, vn, f�� ���� �±� ���ſ�

		if (line[0] == 'v') {              // �� �� ���ڰ� v�̸� ������ ���� �����̴�
			if (line[1] == 'n') {          // vn == ���� ���
				ReadVertex(sstream, vertexNormals);
			}
			else if (line[1] == 't') {		// vt == �ؽ��� ��ǥ
				ReadVertexTexture(sstream, vertexTextureCoord);
			}
			else if (line[1] == ' ') {     // v == ���� ��ǥ
				ReadVertexNormal(sstream, vertexPositions);
			}
		}
		else if (line[0] == 'f') {         // �� �� ���ڰ� f�̸� face(��)�� ���� �����̴�
			ReadFace(sstream, indiciesVec);
		}
	}

	// ���� ��ְ� �ؽ����� ������ ���� �� �ٸ��� ������ ���̻� DrawElements�� ����ϱ�� �����
	// ���� �������� ������
	m_verticies.resize(indiciesVec[0].size());
	auto endLoop{ m_verticies.size() };

	for (auto i = 0; i < endLoop; ++i) {
		m_verticies[i].position = vertexPositions[indiciesVec[0][i]];
		if (!indiciesVec[1].empty()) m_verticies[i].texture = vertexTextureCoord[indiciesVec[1][i]];
		if (!indiciesVec[2].empty()) m_verticies[i].normal = vertexNormals[indiciesVec[2][i]];
	}

	std::cout << m_verticies.size() << std::endl;

	// �� ���� �ּ� �ִ��� ����� ������ �ϱ����� �ߺ����� ���� ���� �迭�� ��꿡 ���
	m_noDuplicatedVertex = vertexPositions;

	CalcMinMaxVertexElem();
	MakeBoundingBox();
}

void Model::SetPatchParameters(int numOfPatches) {
	m_graphicsBuffer->SetPatchParameters(numOfPatches);
}

void Model::SetDrawMode(int drawMode) {
	m_graphicsBuffer->SetDrawMode(drawMode);
}

bool Model::ExistTexture() const {
	return bool{ m_textureComponent };
}

void Model::MakeSierpinskiTriangle(const int& level) {
	CreateSierpinski(level);
	m_graphicsBuffer.release();
	m_graphicsBuffer = std::make_unique<GraphicBuffers>();
	m_graphicsBuffer->Init();
	m_graphicsBuffer->SetVerticies(m_verticies);
}

void Model::Init() {
	m_graphicsBuffer = std::make_unique<GraphicBuffers>();
	m_graphicsBuffer->Init();

	m_graphicsBuffer->SetVerticies(m_verticies);
}

void Model::Update() {
}

void Model::Render() {
	if (m_textureComponent) {
		m_textureComponent->BindingTexture(0);
		OBJECTSHADER->SetUniformBool("notextureID", false);
	}
	else {
		OBJECTSHADER->SetUniformBool("notextureID", true);
	}

	m_graphicsBuffer->Render();
}