#version 460 core

layout(location=0) in vec3 in_Position;

uniform mat4 perspective;
uniform mat4 view;

out vec3 texCoord;

void main(void) 
{
	texCoord = in_Position;
	vec4 position = perspective * view * vec4(in_Position, 1.0f);
	gl_Position = position.xyww;
}