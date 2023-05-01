#include "bullet.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;

constexpr int RANGE = 200;
constexpr int RANGEE = 400;

Bullet::Bullet(Sprite* sprite, vec2 posOrigin, vec2 posDestination, bool enemyBullet)
{
	this->sprite = sprite;
	this->position = posOrigin;
	this->posOrigin = posOrigin;
	this->width = sprite->GetWidth();
	this->height = sprite->GetHeight();
	this->enemyBullet = enemyBullet;
	if (this->enemyBullet)
	{
		this->maxSpeed = 5.0f;
	}
	else
	{
		this->maxSpeed = 10.0f;
	}


	//calculating the angle at which the bullet shoul fly
	vec2 aimDir = posDestination - posOrigin;
	this->aimDirNorm = aimDir.normalized();
	currentv = aimDirNorm * maxSpeed;

	//this->body.setPosition(position);
	//this->body.setSize(vec2(width, height));
}

//void Bullet::setPosition(vec2 posOrigin)
//{
//	if (newPosition == zero)
//	{
//		position.x = posOrigin.x;
//		position.y = posOrigin.y;
//	}
//}

void Bullet::Move(Surface* screen)
{
	position += currentv;
	vec2 travelDistance = position - posOrigin;

	if (position.x < TILESIZE || position.x > BufferWidth - TILESIZE || position.y < TILESIZE || position.y > BufferHeight - TILESIZE)
	{
		destroy = true;
		return;
	}
	
	if (enemyBullet)
	{
		if (travelDistance.x > RANGEE || travelDistance.x < -RANGEE || travelDistance.y > RANGEE || travelDistance.y < -RANGEE)
		{
			destroy = true;
			return;
		}
	}
	else
	{
		if (travelDistance.x > RANGE || travelDistance.x < -RANGE || travelDistance.y > RANGE || travelDistance.y < -RANGE)
		{
			destroy = true;
			return;
		}
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