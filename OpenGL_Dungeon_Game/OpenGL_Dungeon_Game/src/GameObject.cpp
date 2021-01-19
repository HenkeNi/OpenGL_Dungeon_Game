#include "GameObject.h"
#include <iostream>

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : m_position(pos), m_size(size), m_velocity(velocity), m_color(color), m_rotation(0.0f), m_sprite(sprite), m_isSolid(false), m_isDestroyed(false) 
{ 
}

void GameObject::draw(SpriteRenderer& renderer)
{
    renderer.drawSprite(m_sprite, m_position, m_size, m_rotation, m_color);
}

void GameObject::move(glm::vec2 pos)
{
    if (!m_isDestroyed) // only move object if it still exists(?) 
        m_position = pos;
}

bool GameObject::isColliding(const GameObject& otherObject)
{
   // check for collision on x-axis (NOTE: position refers to upper left corner)
    bool collisionXAxis = m_position.x + m_size.x >= otherObject.m_position.x &&
        otherObject.m_position.x + otherObject.m_size.x >= m_position.x;
    // check for collision on y-axis
    bool collisionYAxis = m_position.y + m_size.y >= otherObject.m_position.y &&
        otherObject.m_position.y + otherObject.m_size.y >= m_position.y;

    return collisionXAxis && collisionYAxis; // collision only if on both axes
}

// NOT WORKING:
// 1. GLiding on bottom plane and pressing:  bottom + left
// 2. gliding on left side: left + up
// 3. glinding on right side: right + up
// 4. gliding on top side/plane: up + left
void GameObject::preventCollision(const GameObject& otherObject) 
{
    // Checks from which direction the current object collids with the 'otherObject' and how much the current 
    // object enters/penetrates the otherObject. It then moves the currentObject back in the same direction with equal distance as the penetration

    auto objectMiddleX = otherObject.m_position.x + (otherObject.m_size.x / 2); // middle (x) of object colliding with
    auto objectMiddleY = otherObject.m_position.y + (otherObject.m_size.y / 2);
     
    // TODO: ONLY CHECK WHICH DIRECTION IT ENTERED AND RETURN IT THE SAME DIRECTION?!??

    if (m_position.x > objectMiddleX) // Direction of intersection: RIGHT 
    {
        std::cout << "GOING RIGHT\n";
        float xIntersection = (otherObject.m_position.x + otherObject.m_size.x) - m_position.x; // Amount of intersection on x-axis
        m_position.x += (xIntersection + 0.1f); // place current object to distance equal to penetration - before the collision (plus 1)
    }
    if ((m_position.x + m_size.x) < objectMiddleX) // Direction of intersection: LEFT
    {
        float xIntersection = otherObject.m_position.x - (m_position.x + m_size.x);
        m_position.x += (xIntersection - 0.1f);
    }
    if (m_position.y > objectMiddleY) // Direction of intersection: bottom
    {
        float yIntersection = (otherObject.m_position.y + otherObject.m_size.y) - m_position.y;
        m_position.y += (yIntersection + 0.1f);
    }
    if ((m_position.y + m_size.y) < objectMiddleY) // Direction of intersectionn: top
    {
        float yIntersection = otherObject.m_position.y - (m_position.y + m_size.y);
        m_position.y += (yIntersection - 0.1f);
    }
}











void GameObject::setIsSolid(bool state)
{
    m_isSolid = state;
}

void GameObject::setPositionX(float xPos)
{
    m_position.x = xPos;
}

void GameObject::setPositionY(float yPos)
{
    m_position.y = yPos;
}

bool GameObject::getIsDestroyed() const
{
    return m_isDestroyed;
}

bool GameObject::getIsSolid() const
{
    return m_isSolid;
}

glm::vec2 GameObject::getPosition() const
{
    return m_position;
}

glm::vec2 GameObject::getSize() const
{
    return m_size;
}
