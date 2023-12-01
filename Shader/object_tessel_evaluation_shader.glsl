#version 460 core

// 패치의 종류는 삼각형, ccw정렬로 설정
// 중간의 변수는 보간하는 간격을 조정하는 변수 (equal spacing -> 일정 간격으로 보간)
layout (triangles, equal_spacing, ccw) in;

// 테셀레이션 쉐이더에서 모든 input은 배열 형태여야함 -> 패치 형태로 입력이 오기 떄문
in vec3 fragPositions[];
out vec3 fragPosition;

in vec2 textureCoords[];
out vec2 texCoord;

in vec3 normals[];
out vec3 vNormal;


void main(void)
{
	// 배지어 패치의 가중치 받아오기
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float w = gl_TessCoord.z;

	// 배지어 패치의 컨트롤 포인트 설정
	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;

	// 컨트롤 포인트에 가중치를 곱하고 더한 보간을 통해 새로운 정점 생성
	vec4 p = u * p0 + v * p1 + w * p2;

	// 프래그먼트 위치, 텍스쳐UV, 노멀 벡터도 새롭게 생성된 정점에 따라 새로 생성
	vec2 textureUV = u * textureCoords[0]  + v * textureCoords[1] + w * textureCoords[2];
	vec3 normalVec = u * normals[0] + v * normals[1] + w * normals[2];
	vec3 fragPos = u * fragPositions[0] + v * fragPositions[1] + w * fragPositions[2];

	// 최종 위치를 설정
	gl_Position = p;

	// 최종 텍스쳐UV, 노멀, 프래그먼트 위치 설정
	texCoord = textureUV;
	vNormal = normalVec;
	fragPosition = fragPos;
}