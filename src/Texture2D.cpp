#include "Texture2D.hpp"
#include <glad/glad.h>
#include "Log.hh"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Simplex3D
{

	Texture2D::Texture2D()
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	Texture2D::Texture2D(const char* file_path)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (!loadFromFile(file_path))
			printf("Texture ERRRROROROROROROR");
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(sizeof(unsigned int), &m_texture);
	}

	Texture2D::operator unsigned int() const noexcept
	{
		return m_texture;
	}

	bool Texture2D::loadFromFile(const char* file_path)
	{
		m_data = stbi_load(file_path, &m_width, &m_height, &m_nr_channels, 0);
		if (m_data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(m_data);
			return true;
		}
		log("Failed to load texture!");
		stbi_image_free(m_data);
		return false;
	}
}