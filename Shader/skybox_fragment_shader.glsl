#version 460 core

in vec3 texCoord;

out vec4 FragColor;

uniform samplerCube cubeMapTexture;

void main(void)
{
	FragColor = texture(cubeMapTexture, texCoord);
}