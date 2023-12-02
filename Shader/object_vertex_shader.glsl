#version 460 core
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- 위치 변수: attribute position 0
layout (location = 1) in vec2 in_Texture; //--- 텍스처 변수: attribute position 1
layout (location = 2) in vec3 in_Normal; //--- 정점 노멀 변수: attribute position 2

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 transform;

// lighting
out vec3 vs_out_normal;
out vec2 vs_out_texture;
out vec3 vs_out_fragPosition;

void main(void)
{
	vs_out_fragPosition = vec3(transform * vec4(in_Position, 1.0f));
	vs_out_normal = mat3(transpose(inverse(transform))) * in_Normal;
	vs_out_texture = in_Texture;

	gl_Position = perspective * view * vec4(vs_out_fragPosition, 1.0f);
}