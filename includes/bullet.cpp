#include "bullet.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;

Bullet::Bullet(Sprite* sprite, vec2 playerPos, vec2 mousePos, vec2 directionNorm)
{
	this->sprite = sprite;
	this->position = playerPos;
	this->newPosition = newPosition;
	this->width = sprite->GetWidth();
	this->height = sprite->GetHeight();

	currentv = directionNorm * maxSpeed;

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
		delete this;
		return;
	}
	sprite->Draw(screen, position.x, position.y);
}

//void Bullet::setVelocity(vec2 directionNorm)
//{
//	currentv = directionNorm * maxSpeed;
//}

//void Bullet::Draw(Tmpl8::Surface* screen)
//{
//	sprite->Draw(screen, position.x, position.y);
//}