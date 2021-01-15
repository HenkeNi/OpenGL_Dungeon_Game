#pragma once
#include "Shader.h"
#include "Texture2D.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader &shader);
	~SpriteRenderer();

	void drawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	void initRenderData();

private:
	Shader		  m_shader;
	unsigned int  m_quadVAO;
};

