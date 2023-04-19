#pragma once

#include "../surface.h"
#include "../game.h"

using namespace Tmpl8;

constexpr int FULLHP = 3;

class Player
{
public:
	vec2 playerPos;
	Player(Sprite* sprite);
	
	void Player::Move();

	void Draw(Surface* screen);

private:
	Sprite* sprite = nullptr;
	int health = FULLHP;
	int width, height;
};