#include "pch.h"
#include "Terrain.h"
#include "Graphics/GraphicBuffers.h"
#include "Util/TextureComponent.h"
#include "Graphics/Shader.h"

Terrain::Terrain(const glm::uvec2& mapSize) : m_terrainMapSize{ mapSize } {
	TERRAINSHADER->UseProgram();
	// 먼저 하이트맵의 텍스쳐를 불러옴
	m_textureComponent = std::make_unique<TextureComponent>();
	m_textureComponent->LoadTexture(".\\textures\\height1.png", false);
	m_textureComponent->LoadTexture(".\\textures\\terrain1.png", false);

	m_vertexBuffer = std::make_unique<GraphicBuffers>();
	m_vertexBuffer->Init();

	CreateTerrainMeshMap();
	m_vertexBuffer->SetVerticies(m_verticies);

	Init();
	TERRAINSHADER->UnUseProgram();
}

Terrain::~Terrain() { }

void Terrain::CreateTerrainMeshMap() {
	auto heightMapInfo = m_textureComponent->GetTextureInfo(HEIGHT_MAP);
	float tileWidth = heightMapInfo.width / static_cast<float>(m_terrainMapSize.x);
	float tileHeight = heightMapInfo.height / static_cast<float>(m_terrainMapSize.y);
	float left = (-heightMapInfo.width / 2.f);
	float bottom = (-heightMapInfo.height / 2.f);
	glm::vec3 terrainNorm{ 0.f, 1.f, 0.f };
	// xz평면 상에 지형을 그려줄 큐브 메쉬들의 정점을 생성함
	for (unsigned int x = 0; x < m_terrainMapSize.x; ++x) {
		for (unsigned int z = 0; z < m_terrainMapSize.y; ++z) {
			// 중앙을 0,0으로 잡고 왼쪽에서 부터 오른쪽으로 만듬
			// 공식은 이미지 너비의 반을 hw, 높이의 반을 hh라 하면 
			// i는 타일맵 으로 생각할때 타일 맵의 번호
			// -hw + w * ((i + 1 or + 0) / mapSize) -> hw를 왼쪽 오른쪽이라 생각하면 각 타일의 너비 높이는 w / mapsize.x, h / mapsize.z 이므로
			// left + (x * (w / mapsize.x), bottom + (z * (h / mapsize.z))
			// xz평면 상에 생성할 것이므로 y좌표는 항상 0
			// 텍스쳐 좌표는 정규화된 좌표이므로 0,1 사이에 존재해야함 따라서 
			// u,v = x / mapsize.x, z / mapsize.z
			Vertex p0{
				glm::vec3{
					left + static_cast<float>(x * tileWidth),
					0.f,
					bottom + static_cast<float>(z * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x) / m_terrainMapSize.x, static_cast<float>(z) / m_terrainMapSize.y
				},
				terrainNorm
			};

			Vertex p1{
				glm::vec3{
					left + static_cast<float>((x + 1) * tileWidth),
					0.f,
					bottom + static_cast<float>((z * tileHeight))
				},
				glm::vec2{
					static_cast<float>(x + 1) / m_terrainMapSize.x, static_cast<float>(z) / m_terrainMapSize.y
				},
				terrainNorm
			};

			Vertex p2{
				glm::vec3{
					left + static_cast<float>(x * tileWidth),
					0.f,
					bottom + static_cast<float>((z + 1) * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x) / m_terrainMapSize.x, static_cast<float>(z + 1) / m_terrainMapSize.y
				},
				terrainNorm
			};

			Vertex p3{
				glm::vec3{
					left + static_cast<float>((x + 1) * tileWidth),
					0.f,
					bottom + static_cast<float>((z + 1) * tileHeight)
				},
				glm::vec2{
					static_cast<float>(x + 1) / m_terrainMapSize.x, static_cast<float>(z + 1) / m_terrainMapSize.y
				},
				terrainNorm
			};

			m_verticies.push_back(p0);
			m_verticies.push_back(p2);
			m_verticies.push_back(p1);
			m_verticies.push_back(p3);
		}
	}

	std::cout << "creating terrain success : \n\tterrain patch size{ " << m_terrainMapSize.x << " x " << m_terrainMapSize.x << " }, "
		<< "\n\tterrain vertex size{ " << m_verticies.size() << " }\n";
}

void Terrain::CreateTerrainVertexBuffers() {
	TERRAINSHADER->UseProgram();

	// 지형을 그릴 VAO, VBO생성 및 정점 바인딩
	glBufferData(GL_ARRAY_BUFFER, uint32(m_verticies.size()) * sizeof(Vertex), &m_verticies[0], GL_STATIC_DRAW);

	// location 0번에 Vertex객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Vertex객체의 texture정보를 넘겨줌
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);

	// location 2번에 Vertex객체의 normal정보를 넘겨줌
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	// 사각형 패치로 넘겨줌
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	TERRAINSHADER->UnUseProgram();
}

void Terrain::Init() {

}

void Terrain::Update(float deltaTime) {

}

void Terrain::Render() {
	TERRAINSHADER->UseProgram();
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_textureID);
	//glBindVertexArray(m_terrainVAO);
	//glDrawArrays(GL_PATCHES, 0, uint32(m_verticies.size()));
	//glBindVertexArray(0);
	m_textureComponent->BindingTexture(HEIGHT_MAP);
	m_textureComponent->BindingTexture(TERRAIN_TEX);
	TERRAINSHADER->SetUniformInt("heightMap", 0);
	TERRAINSHADER->SetUniformInt("heightMapTexture", 1);
	m_vertexBuffer->SetDrawMode(GL_PATCHES);
	m_vertexBuffer->SetPatchParameters(4);
	m_vertexBuffer->Render();
	TERRAINSHADER->UnUseProgram();
}
