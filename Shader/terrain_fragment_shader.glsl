#version 460 core

in float height;
in vec2 tes_out_tex;
out vec4 fragColor;

uniform sampler2D heightMapTexture;

void main(void)
{
	float heightColor = (height + 64.0f) / 128.0f;

	vec3 texColor = vec3(texture(heightMapTexture, tes_out_tex));

	fragColor = vec4(texColor, 1.0f);
}