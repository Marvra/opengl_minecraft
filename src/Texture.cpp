#include "Texture.h"

Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;

	int imgWidth, imgHeight, imgClrChannels;
	unsigned char *bytes = stbi_load(image, &imgWidth, &imgHeight, &imgClrChannels, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
