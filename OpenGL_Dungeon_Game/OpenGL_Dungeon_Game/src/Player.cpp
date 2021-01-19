#include "Player.h"


Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: GameObject(pos, size, sprite, color, velocity)
{

}




/*glm::vec2 Player1::move(float dt, unsigned int windowWidth)
{
	if (!isAlive()) { return glm::vec2(0.0f, 0.0f); } // CORRECT OR WILL CHANGE POSITION??!?!?!
	
	m_position = position;
}*/

void Player::resetPlayerPosition(glm::vec2 position, glm::vec2 velocity)
{

}


bool Player::isAlive() const
{
	return m_healthPoints > 0;
}