#pragma once
#include "../surface.h"
#include "../game.h"

using Tmpl8::Sprite;
using sf::Vector2f;

class Bullet 
{
public:
	Bullet(Sprite* sprite, Vector2f playerPos, Vector2f mousePos);

	//void Draw(Tmpl8::Surface* screen);

	void setPosition(Vector2f playerpos);

	void Move(Tmpl8::Surface* screen);

	void setVelocity(Vector2f directionNorm);

private:
	Sprite* sprite = nullptr;

	Vector2f currentv;
	float maxSpeed = 10.0f;
	Vector2f zero;

	Vector2f position;
	Vector2f newPosition;
	bool destroy = false;
};