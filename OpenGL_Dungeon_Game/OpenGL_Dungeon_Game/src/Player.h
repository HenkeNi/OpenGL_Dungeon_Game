#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	//glm::vec2 move(float dt, unsigned int windowWidth);
	void resetPlayerPosition(glm::vec2 position, glm::vec2 velocity);
	bool isAlive() const;
private:
	int m_healthPoints{ 3 };
};

