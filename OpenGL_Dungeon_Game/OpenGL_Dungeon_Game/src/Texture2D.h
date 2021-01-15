#pragma once
#include <GL/glew.h>

class Texture2D
{
public:
	Texture2D();
	
	void generate(unsigned int width, unsigned int height, unsigned char* data); // generates texture from image data
	void bind() const; // binds texture as current active GL_TEXTURE_2D texture object

	void setInternalFormat(unsigned int format);
	void setImageFormat(unsigned int format);
	unsigned int& getId();

private:
	unsigned int m_id;							// id of texture object
	unsigned int m_width{ 0 }, m_height{ 0 };   // width and height of loaded image in pixels
	unsigned int m_internalFormat{ GL_RGB };	// format of texture object
	unsigned int m_imageFormat{ GL_RGB };		// format of loaded image

	unsigned int m_wrapS	 { GL_REPEAT };		// wrapping mode on s-axis
	unsigned int m_wrapT	 { GL_REPEAT };		// wrapping mode on t-axis
	unsigned int m_filterMin { GL_LINEAR };		// filtering mode if texture pixels < screen pixels
	unsigned int m_filterMax { GL_LINEAR };		// filtering mode if texture pixels > screen pixels
};

