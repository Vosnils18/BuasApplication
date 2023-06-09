#pragma once

#include "../surface.h"
#include "../game.h"
#include "../template.h"
#include "../collider.h"

using namespace Tmpl8;

class Player
{
public:
	Player(Sprite* spriteIdle, Sprite* spriteIdleRed, Sprite* spriteRun, Sprite* spriteRunRed);
	
	void Update(float deltaTime);

	void Draw(Surface* screen);

	void DealDamage(int damage);

	Collider GetCollider()
	{
		return Collider(position, vec2(width, height));
	}

	vec2 position;
	int health;
	int attackTimer;
	int invincibilityTimer;

private:
	Sprite* spriteIdle = nullptr;
	Sprite* spriteIdleRed = nullptr;
	Sprite* spriteRun = nullptr;
	Sprite* spriteRunRed = nullptr;
	Sprite* activeSprite = nullptr;

	int animationFrame;
	bool running;
	bool lookingLeft;

	int width, height;
};