#pragma once

#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using namespace Tmpl8;

class ImpEnemy
{
public:
	ImpEnemy(Sprite* spriteIdle, Sprite* spriteRun, Sprite* bouncySprite, int isShooter, bool isBouncy);

	void setPosition(vec2 pos);

	void Update(float deltaTime, vec2 playerPos);

	void Rage(vec2 position, vec2 playerPos);

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
	bool isBouncy;
	int health;

private:
	Sprite* spriteIdle = nullptr;
	Sprite* spriteRun = nullptr;
	Sprite* activeSprite = nullptr;
	Sprite* bouncySprite = nullptr;
	
	int animationFrame;
	bool lookingLeft;

	vec2 positionHitBox;
	float enemyMoveTimer;
	int direction;
	
	bool running;
	bool rage;

	float speed;
	vec2 currentv;
	int width, height;
};