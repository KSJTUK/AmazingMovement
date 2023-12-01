#pragma once

class TextureComponent {
public:
	TextureComponent();
	~TextureComponent();

private:
	std::vector<TextureInfo> m_textures{ };
	std::vector<CubeMapInfo> m_cubeMaps{ };

public:
	void SetTextureDefaultOption();
	void LoadTexture(const std::string& textureFilePath, bool flipImageOnLoad);

	void BindingTexture(int textureIndex);
	void UnBindingTextures();

	uint32 GetTextureID(int textureIndex);
	const TextureInfo& GetTextureInfo(int textureIndex) const;
};

class CubeMapTexture {
public:
	CubeMapTexture();
	~CubeMapTexture();

private:
	std::vector<CubeMapInfo> m_cubeMaps{ };

public:
	void SetCubeMapTextureOption();

	void LoadCubeMapTexture(const std::string& posX, const std::string& negX, const std::string& posY,
		const std::string& negY, const std::string& posZ, const std::string& negZ, bool);

	void BindCubeMap(int cubeMapIndex);
	void BindCubeMap();
	void UnBindCubeMap();
};