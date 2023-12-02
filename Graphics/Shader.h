#pragma once

class Shader abstract {
protected:
	Shader();
	virtual ~Shader();

protected:
	unsigned int m_shaderProgram{ };
	unsigned int m_fragmentShader{ };
	unsigned int m_vertexShader{ };
	unsigned int m_tesselControlShader{ };
	unsigned int m_tesselEvaluationShader{ };
	unsigned int m_geometryShader{ };

	// 쉐이더 파일의 내용을 저장할 변수
	std::string m_vertexShaderFileContents{ };
	std::string m_fragmentShaderFileContents{ };
	std::string m_tesselationControlFileContents{ };
	std::string m_tesselationEvaluationFileContents{ };
	std::string m_geometryShaderFileContents{ };

	std::unordered_map<std::string, int32> m_uniformLocationCache{ };

public:
	int32 FindLocation(const std::string& name);

	// 쉐이더 파일 내용을 불러오는 함수
	void LoadVertexShaderFile(const char* filePath);
	void LoadFragmentShaderFile(const char* filePaht);
	void LoadTesselationControlShaderFile(const char* filePath);
	void LoadTesselationEvaluationShaderFile(const char* filePath);
	void LoadGeometryShader(const char* filePath);

	// 쉐이더 작성 함수들
	virtual void CompileShaders() = 0;
	virtual void AttachAndLinkShaders() = 0;
	virtual void CreateShaderProgram() = 0;

	// program 사용
	void UseProgram();
	void UnUseProgram();

	// 에러 검출 함수
	void CheckAndPrintShaderCompileError(const uint32& shaderID);

	// 유니폼 변수들 세팅 함수
	void SetUniformMat4(const std::string& valName, const glm::mat4& matrix);
	void SetUniformMat3(const std::string& valName, const glm::mat3& matrix);
	void SetUniformMat2(const std::string& valName, const glm::mat2& matrix);
	void SetUniformVec4(const std::string& valName, const glm::vec4& vector);
	void SetUniformVec3(const std::string& valName, const glm::vec3& vector);
	void SetUniformVec2(const std::string& valName, const glm::vec2& vector);
	void SetUniformFloat(const std::string& valueName, const float& fValue);
	void SetUniformInt(const std::string& valName, const int& iValue);
	void SetUniformBool(const std::string& valName, const int& bValue);

public:
	// Getter 함수들
	unsigned int GetShaderProgramID() const { return m_shaderProgram; }
};

class ObjectShader : public Shader {
private:
	ObjectShader();
	~ObjectShader();

private:
	static ObjectShader* m_instance;

public:
	static ObjectShader* GetInstance();
	static void Destroy();

public:

	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();
};


class LightObjectShader : public Shader {
private:
	LightObjectShader();
	~LightObjectShader();

private:
	static LightObjectShader* m_instance;

public:
	static LightObjectShader* GetInstance();
	static void Destroy();

public:

	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();
};

class ParticleShader : public Shader {
private:
	ParticleShader();
	~ParticleShader();

private:
	static ParticleShader* m_instance;

public:
	static ParticleShader* GetInstance();
	static void Destroy();

public:
	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();
};

class TerrainShader : public Shader {
private:
	TerrainShader();
	~TerrainShader();

private:
	static TerrainShader* m_instance;

public:
	static TerrainShader* GetInstance();
	static void Destroy();

public:
	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();
};

class BackGroundShader : public Shader {
private:
	BackGroundShader();
	~BackGroundShader();

private:
	static BackGroundShader* m_instance;

public:
	static BackGroundShader* GetInstance();
	static void Destroy();

public:
	// 쉐이더 작성 함수들
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();
};