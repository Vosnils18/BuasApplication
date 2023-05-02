#pragma once

#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using namespace Tmpl8;

class Enemy
{
public:
	Enemy(Sprite* spriteIdle, Sprite* spriteRun, int isShooter);

	void setPosition(vec2 pos);

	void Update(float deltaTime, vec2 playerPos);

	void Draw(Tmpl8::Surface* screen);

	Collider GetCollider() 
	{
		return Collider(positionHitBox, vec2(width, height));
	}

	bool playerInRange(float low, float high, float x)
	{
		return (low <= x && x <= high);
	}

	bool dropsHeart()
	{
		if (isShooter % 8 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool destroy = false;
	vec2 position;
	int attackTimer;
	bool followPlayer;
	int isShooter;

private:
	Sprite* spriteIdle = nullptr;
	Sprite* spriteRun = nullptr;
	Sprite* activeSprite = nullptr;

	int enemyMoveTimer;
	int direction;
	vec2 positionHitBox;
	
	bool running;
	int animationFrame;
	bool lookingLeft;

	float speed;
	vec2 currentv;
	int width, height;
};