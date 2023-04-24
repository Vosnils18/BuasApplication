#pragma once
#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using namespace Tmpl8;

class Bullet 
{
public:
	Bullet(Sprite* sprite, vec2 playerPos, vec2 mousePos, vec2 directionNorm);

	//void Draw(Tmpl8::Surface* screen);

	//void setPosition(vec2 playerpos);

	void Move(Tmpl8::Surface* screen);

	//void setVelocity(vec2 directionNorm);

	Collider GetCollider() 
	{ 
		return Collider(position, vec2(width, height)); 
	}

	bool destroy = false;

private:
	Sprite* sprite = nullptr;

	vec2 currentv;
	float maxSpeed = 10.0f;

	int width, height;
	vec2 position;
	vec2 newPosition;
};