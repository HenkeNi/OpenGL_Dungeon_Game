#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
	: m_state{ GameState::GAME_ACTIVE }, m_keys(), m_width { width }, m_height{ height }
{
}

Game::~Game()
{
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
	ResourceManager::loadTexture("src/textures/awesomeface.png", true, "face");

}

void Game::update(float dt)
{
}

void Game::processInput(float dt)
{
}

void Game::render()
{
	Renderer->drawSprite(ResourceManager::getTexture("face"),
		glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::setKey(int key, bool active)
{
	m_keys[key] = active;
}