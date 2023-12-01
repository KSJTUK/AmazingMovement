#pragma once

enum TerrainTex {
	HEIGHT_MAP = 0,
	TERRAIN_TEX
};

class Terrain {
public:
	Terrain(const glm::uvec2& mapSize);
	~Terrain();

private:
	glm::uvec2 m_terrainMapSize{ };
	std::vector<Vertex> m_verticies{ };

	std::unique_ptr<class TextureComponent> m_textureComponent{ };

	std::unique_ptr<class GraphicBuffers> m_vertexBuffer{ };

private:
	void CreateTerrainMeshMap();
	void CreateTerrainVertexBuffers();

public:
	void Init();
	void Update(float deltaTime);
	void Render();

};