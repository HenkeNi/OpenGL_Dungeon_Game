#include "Texture2D.h"

Texture2D::Texture2D()
{
	glGenTextures(1, &m_id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
	m_width = width;
	m_height = height;

	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::setInternalFormat(unsigned int format)
{
	m_internalFormat = format;
}

void Texture2D::setImageFormat(unsigned int format)
{
	m_imageFormat = format;
}

unsigned int& Texture2D::getId()
{
	return m_id;
}