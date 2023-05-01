#pragma once
#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using namespace Tmpl8;

class Bullet 
{
public:
	Bullet(Sprite* sprite, vec2 posOrigin, vec2 posDestination, bool enemyBullet);

	//void Draw(Tmpl8::Surface* screen);

	//void setPosition(vec2 posOrigin);

	void Move(Tmpl8::Surface* screen);

	//void setVelocity(vec2 directionNorm);

	Collider GetCollider() 
	{ 
		return Collider(position, vec2(width, height)); 
	}

	bool destroy = false;
	bool enemyBullet = false;
	vec2 posOrigin;

private:
	Sprite* sprite = nullptr;

	vec2 currentv;
	float maxSpeed;
	vec2 aimDirNorm;

	int width, height;
	vec2 position;
};