#version 460 core

in vec4 gs_out_color;
in vec2 gs_out_tex;

out vec4 FragColor;

void main(void)
{
	FragColor = gs_out_color;
}