#pragma once
#include "GameState.h"
#include "GameLevel.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

const glm::vec2 playerSize(40.0f, 40.0f);
const float playerVelocity(500.0f);


class Game
{
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void init(); // initialize game state (load all shaders/textures/levels

	void processInput(float dt);
	void update(float dt);
	void render();

	void doCollisions();
	void setKey(int key, bool active);

private:
	GameState    m_state;
	bool	     m_keys[1024];
	unsigned int m_width, m_height;

	std::vector<GameLevel> m_levels;
	unsigned int		   m_level{ 0 };
};

