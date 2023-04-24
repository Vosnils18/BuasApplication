#pragma once

#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using namespace Tmpl8;

class Enemy
{
public:
	Enemy(Sprite* sprite);

	void setPosition();

	void Move();

	void Draw(Tmpl8::Surface* screen);

	Collider GetCollider() 
	{
		return Collider(position, vec2(width, height));
	}

	bool destroy = false;

private:
	Sprite* sprite = nullptr;

	vec2 position;
	int enemyMoveTimer = 0;

	float speed;
	vec2 currentv;
	int width, height;
};