#pragma once
#include "../surface.h"
#include "../game.h"
#include "../collider.h"
#include <SFML/Graphics/Rect.hpp>

using namespace Tmpl8;

class Bullet 
{
public:
	Bullet(Sprite* sprite, vec2 playerPos, vec2 mousePos);

	//void Draw(Tmpl8::Surface* screen);

	//void setPosition(vec2 playerpos);

	void Move(Tmpl8::Surface* screen);

	void setVelocity(vec2 directionNorm);

	Collider GetCollider() { return Collider(body); }

private:
	Sprite* sprite = nullptr;
	sf::Rect<float> body;

	vec2 currentv;
	float maxSpeed = 10.0f;
	vec2 zero;

	int width, height;
	vec2 position;
	vec2 newPosition;
};