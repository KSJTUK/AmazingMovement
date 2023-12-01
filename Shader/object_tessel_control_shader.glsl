#version 460 core

// vertices = 3 -> 삼각형 패치를 사용 
// 나가는 정점 3개를 정의
layout (vertices = 3) out;

in vec3 fragPosition[];
out vec3 fragPositions[];

in vec3 vNormal[];
out vec3 normals[];

in vec2 texCoord[];
out vec2 textureCoords[];

uniform vec3 viewPositionForDynamicTessel;

const int maxTesselLevel = 10;
const int minTesselLevel = 2;

const float maxTesselDist = 1.5f;
const float minTesselDist = 0.1f;

const int tesselLevel = 1;

void main()
{
	// 삼각형 패치에서 외부 정점에 대해 수행항 테셀레이션 레벨을 설정 (최대 5)
	gl_TessLevelOuter[0] = tesselLevel;
	gl_TessLevelOuter[1] = tesselLevel;
	gl_TessLevelOuter[2] = tesselLevel;

	// 삼각형 패치 내부 정점에 대해 수행할 테셀레이션 레벨을 설정 (마찬가지로 최대 5)
	gl_TessLevelInner[0] = tesselLevel;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	textureCoords[gl_InvocationID] = texCoord[gl_InvocationID];
	normals[gl_InvocationID] = vNormal[gl_InvocationID];
	fragPositions[gl_InvocationID] = fragPosition[gl_InvocationID];
}