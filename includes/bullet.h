#pragma once
#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using namespace Tmpl8;

class Bullet 
{
public:
	Bullet(Sprite* sprite, vec2 posOrigin, vec2 posDestination, bool enemyBullet);

	void Move(Tmpl8::Surface* screen);

	Collider GetCollider() 
	{ 
		return Collider(positionHitBox, vec2(width, height)); 
	}

	bool destroy = false;
	bool enemyBullet = false;
	
	vec2 posOrigin;

private:
	Sprite* sprite = nullptr;
	int animationFrame;

	vec2 currentv;
	float maxSpeed;
	vec2 aimDirNorm;
	int hitWall;

	int width, height;
	vec2 position;
	vec2 positionHitBox;
};