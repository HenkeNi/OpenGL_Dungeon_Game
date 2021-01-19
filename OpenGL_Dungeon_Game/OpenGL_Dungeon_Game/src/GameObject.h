#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	
	virtual ~GameObject() {}

	virtual void draw(SpriteRenderer& renderer);
	
	void move(glm::vec2 pos);
	
	bool isColliding(const GameObject& otherObject);
	void preventCollision(const GameObject& otherObject); // rename: stopIntersection || preventIntersection


	void setIsSolid(bool state);
	void setPositionX(float xPos);
	void setPositionY(float yPos);

	bool	  getIsDestroyed() const;
	bool	  getIsSolid()	   const;
	glm::vec2 getPosition()	   const;
	glm::vec2 getSize()		   const;

protected:
	glm::vec2  m_position{ 0.0f, 0.0f }, m_size{ 1.0f, 1.0f }, m_velocity{ 0.0f };
	glm::vec3  m_color{ 1.0f };
	float	   m_rotation{ 0.0f };
	bool	   m_isSolid{ false };
	bool	   m_isDestroyed{ false };
	Texture2D  m_sprite{};
};

