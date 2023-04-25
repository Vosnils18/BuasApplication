#pragma once

#include "../surface.h"
#include "../game.h"
#include "../template.h"
#include "../collider.h"

using namespace Tmpl8;

class Player
{
public:
	Player(Sprite* spriteIdle, Sprite* spriteRun);
	
	void Player::Update();

	void Draw(Surface* screen);

	void DealDamage(int damage);

	Collider GetCollider()
	{
		return Collider(position, vec2(width, height));
	}

	vec2 position;
	int health;

private:
	Sprite* spriteIdle = nullptr;
	Sprite* spriteRun = nullptr;
	Sprite* activeSprite = nullptr;

	int animationFrame;
	bool running;
	bool lookingLeft;

	int invincibilityTimer;
	int width, height;
};