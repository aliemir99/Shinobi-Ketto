#include "Entity.h"
#include <cassert>

Entity::Entity(int hitPoints)
	:hitPoints(hitPoints)
{
}

void Entity::setVelocity(sf::Vector2f v)
{
	velocity = v;
}

void Entity::setVelocity(float xv, float yv)
{
	velocity.x = xv;
	velocity.y = yv;
}

void Entity::accelerate(sf::Vector2f v)
{
	velocity += v;
}

void Entity::accelerate(float xv, float yv)
{
	velocity.x += xv;
	velocity.y += yv;
}

sf::Vector2f Entity::getVelocity() const
{
	return velocity;
}

int Entity::getHitpoints() const
{
	return hitPoints;
}

void Entity::repair(int points)
{
	assert(points > 0);
	hitPoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);
	hitPoints -= points;
}

void Entity::destroy()
{
	hitPoints = 0;
}

bool Entity::isDestroyed() const
{
	return hitPoints <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	move(velocity * dt.asSeconds());

}
