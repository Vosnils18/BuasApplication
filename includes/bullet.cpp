#include "bullet.h"
#include "../game.h"
#include "../template.h"

using sf::Vector2f;
using namespace Tmpl8;

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
	this->width = sprite->GetWidth();
	this->height = sprite->GetHeight();

	this->body.setPosition(position);
	this->body.setSize(Vector2f(width, height));
}

//void Bullet::setPosition(Vector2f playerPos)
//{
//	if (newPosition == zero)
//	{
//		position.x = playerPos.x;
//		position.y = playerPos.y;
//	}
//}

void Bullet::Move(Surface* screen)
{
	position += currentv;

	if (position.x < TILESIZE || position.x > BufferWidth - TILESIZE || position.y < TILESIZE || position.y > BufferHeight - TILESIZE)
	{
		return;
	}
	sprite->Draw(screen, position.x, position.y);
}

void Bullet::setVelocity(Vector2f directionNorm)
{
	currentv = directionNorm * maxSpeed;
}

//void Bullet::Draw(Tmpl8::Surface* screen)
//{
//	sprite->Draw(screen, position.x, position.y);
//}