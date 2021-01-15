#pragma once
#include "GameState.h"

class Game
{
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void init(); // initialize game state (load all shaders/textures/levels

	void processInput(float dt);
	void update(float dt);
	void render();

	void setKey(int key, bool active);

private:
	GameState    m_state;
	bool	     m_keys[1024];
	unsigned int m_width, m_height;
};

