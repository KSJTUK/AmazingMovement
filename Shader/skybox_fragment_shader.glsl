#version 460 core

in vec3 texCoord;

out vec4 FragColor;

uniform samplerCube cubeMapTexture;

void main(void)
{
//	FragColor = texture(cubeMapTexture, texCoord);
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}