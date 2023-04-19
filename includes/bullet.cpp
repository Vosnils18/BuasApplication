#include "bullet.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;

Bullet::Bullet(Sprite* sprite, vec2 playerPos, vec2 mousePos)
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

	//this->body.setPosition(position);
	//this->body.setSize(vec2(width, height));
}

//void Bullet::setPosition(vec2 playerPos)
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

void Bullet::setVelocity(vec2 directionNorm)
{
	currentv = directionNorm * maxSpeed;
}

//void Bullet::Draw(Tmpl8::Surface* screen)
//{
//	sprite->Draw(screen, position.x, position.y);
//}