#include "bullet.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;

constexpr int RANGE = 480;

Bullet::Bullet(Sprite* sprite, vec2 posOrigin, vec2 posDestination, bool enemyBullet)
{
	this->sprite = sprite;
	this->animationFrame = 0;
	this->position = posOrigin;
	this->posOrigin = posOrigin;
	this->width = 6;
	this->height = 6;
	this->hitWall = 0;
	this->enemyBullet = enemyBullet;
	if (this->enemyBullet)
	{
		this->maxSpeed = 5.0f;
	}
	else
	{
		this->maxSpeed = 10.0f;
	}

	//calculating the angle at which the bullet should fly
	vec2 aimDir = posDestination - posOrigin;
	this->aimDirNorm = aimDir.normalized();
	currentv = aimDirNorm * maxSpeed;
}

void Bullet::Move(Surface* screen)
{
	position += currentv;
	vec2 travelDistance = position - posOrigin;
	positionHitBox.x = position.x + 5;
	positionHitBox.y = position.y + 7;
		
	//check wall collision
	if (position.x < TILESIZE || position.x > BufferWidth - TILESIZE - width)
	{
		if (hitWall >= 2 || enemyBullet)
		{
			destroy = true;
			return;
		}
		else
		{
			currentv.x -= currentv.x * 2;
			hitWall++;
		}
	}
	if (position.y < TILESIZE - 5 || position.y > BufferHeight - TILESIZE - height) 
	{ 
		if (hitWall >= 2 || enemyBullet)
		{
			destroy = true;
			return;
		}
		else
		{
			currentv.y -= currentv.y * 2;
			hitWall++;
		}
	}
	
	//double check for out of bounds bullets
	if (travelDistance.x > RANGE || travelDistance.x < -RANGE || travelDistance.y > RANGE || travelDistance.y < -RANGE)
	{
		destroy = true;
		return;
	}

	//switch animation frames and draw sprite
	if (animationFrame == 0)
	{
		animationFrame = 1;
	}
	else
	{
		animationFrame = 0;
	}
	sprite->SetFrame(animationFrame);
	sprite->Draw(screen, position.x, position.y);
}