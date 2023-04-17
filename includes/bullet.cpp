#include "bullet.h"
#include "../game.h"

using sf::Vector2f;

Bullet::Bullet(Sprite* sprite, Vector2f playerPos, Vector2f mousePos)
{
	this->sprite = sprite;

	if (newPosition == zero)
	{
		this->position = playerPos;
	}
	else
	{
		this->position = newPosition;
	}
	this->newPosition = newPosition;
	this->zero = zero;
}

void Bullet::setPosition(Vector2f playerPos)
{
	if (newPosition == zero)
	{
		position.x = playerPos.x;
		position.y = playerPos.y;
	}
}

void Bullet::Move()
{
	position += currentv;
}

void Bullet::setVelocity(Vector2f directionNorm)
{
	currentv = directionNorm * maxSpeed;
}

void Bullet::Draw(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, position.x, position.y);
}