#include "Game.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include "Player.h"
#include <iostream>

SpriteRenderer* Renderer;
Player* Player2;

Game::Game(unsigned int width, unsigned int height)
	: m_state{ GameState::GAME_ACTIVE }, m_keys(), m_width { width }, m_height{ height }
{
}

Game::~Game()
{
	delete Renderer;
	delete Player2;
}

void Game::init()
{
	// load shaders
	ResourceManager::loadShader("src/shaders/sprite.vs", "src/shaders/sprite.frag", nullptr, "sprite");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use().setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", projection);
	// set render-specific controls	
	Renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	// load textures
	ResourceManager::loadTexture("src/textures/block_solid.png", false, "block_solid");
	ResourceManager::loadTexture("src/textures/awesomeface.png", true, "face");
	ResourceManager::loadTexture("src/textures/block.png", false, "block");
	ResourceManager::loadTexture("src/textures/background.jpg", false, "background");
	ResourceManager::loadTexture("src/textures/paddle.png", true, "paddle");

	// load levels
	GameLevel one; one.load("src/levels/one.lvl", m_width, m_height);

	m_levels.push_back(one);
	m_level = 0;



	glm::vec2 playerPos = glm::vec2(
		m_width / 2 - playerSize.x / 2.0f,
		m_height / 2 - playerSize.y / 2.0f
	);
	Player2 = new Player(playerPos, playerSize, ResourceManager::getTexture("paddle"));

}

void Game::update(float dt)
{
	doCollisions();
}

void Game::processInput(float dt)
{
	if (m_state == GameState::GAME_ACTIVE)
	{
		auto currentPosition = Player2->getPosition();
		float velocity = playerVelocity * dt;
		
		// move player
		if (m_keys[GLFW_KEY_W])
		{
			if (currentPosition.y > 0.0f)
				Player2->move({ currentPosition.x, currentPosition.y -= velocity });
		}
		if (m_keys[GLFW_KEY_S])
		{
			if (currentPosition.y <= m_height - Player2->getSize().y)
				Player2->move({ currentPosition.x, currentPosition.y += velocity });
		}
		if (m_keys[GLFW_KEY_A])
		{
			if (currentPosition.x > 0.0f)
				Player2->move({ currentPosition.x -= velocity, currentPosition.y });
		}
		if (m_keys[GLFW_KEY_D])
		{
			if (currentPosition.x <= m_width - Player2->getSize().x)
				Player2->move({ currentPosition.x += velocity, currentPosition.y });
		}
	}
}

void Game::render()
{
	if (m_state == GameState::GAME_ACTIVE)
	{
		Renderer->drawSprite(ResourceManager::getTexture("background"),
			glm::vec2(0.0f, 0.0f), glm::vec2(m_width, m_height), 0.0f);

		m_levels[m_level].draw(*Renderer);

		Player2->draw(*Renderer);
	}

}

void Game::doCollisions()
{
	for (auto& tile : m_levels[m_level].getTiles())
	{
		if (tile.getIsSolid() && Player2->isColliding(tile))
		{
			Player2->preventCollision(tile);
			 
			//Player2->move(Player2->getPosition() += depth);
			
			
			//std::cout << "HITTING WALL!";
			// CHECK HOW MUCH PENETRATION IN A-AXIS AND THE Y-AXIS -> set movement left and up (for example to false)
			// - also return the penetration and update position with currentPOsition -= penetration on both axis
		}
	}
}

void Game::setKey(int key, bool active)
{
	m_keys[key] = active;
}