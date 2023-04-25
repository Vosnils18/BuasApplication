#pragma once

#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using namespace Tmpl8;

class Enemy
{
public:
	Enemy(Sprite* spriteIdle, Sprite* spriteRun);

	void setPosition();

	void Update();

	void Draw(Tmpl8::Surface* screen);

	Collider GetCollider() 
	{
		return Collider(position, vec2(width, height));
	}

	bool destroy = false;

private:
	Sprite* spriteIdle = nullptr;
	Sprite* spriteRun = nullptr;
	Sprite* activeSprite = nullptr;

	vec2 position;
	int enemyMoveTimer;
	int direction;
	
	bool running;
	int animationFrame;
	bool lookingLeft;

	float speed;
	vec2 currentv;
	int width, height;
};