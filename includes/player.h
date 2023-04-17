#pragma once

#include "../surface.h"
#include "../game.h"

using Tmpl8::Sprite;
using sf::Vector2f;

constexpr int FULLHP = 3;

class Player
{
public:
	Vector2f playerPos;
	Player(Sprite* sprite);
	
	void Player::Move();

	void Draw(Tmpl8::Surface* screen);

private:
	Sprite* sprite = nullptr;
	int health = FULLHP;
	int width, height;
};