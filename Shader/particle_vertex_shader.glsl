#version 460 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_Texture;
layout(location=2) in vec4 in_ParticleColor;

out vec4 vs_out_color;
out vec2 vs_out_tex;

uniform mat4 perspective;
uniform mat4 view;

void main(void)
{
	gl_Position = perspective * view * vec4(in_Position, 1.0f);
	vs_out_color = in_ParticleColor;
	vs_out_tex = in_Texture;
}