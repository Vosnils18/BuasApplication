#pragma once

#include "../surface.h"
#include "../game.h"
#include "../collider.h"

using Tmpl8::Sprite;
using sf::Vector2f;

class Enemy
{
public:
	Enemy(Sprite* sprite);

	void setPosition();

	void Move();

	void Draw(Tmpl8::Surface* screen);

	Collider GetCollider() { return Collider(body); }

private:
	Sprite* sprite = nullptr;

	Vector2f position;
	sf::RectangleShape body;
	float speed;
	Vector2f currentv;
	int width, height;
};