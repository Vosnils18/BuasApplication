#pragma once
#include <SFML/Graphics.hpp>

using namespace Tmpl8;

class Collider
{
public:
	Collider(sf::RectangleShape& body);

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider& other, float force);

	vec2 GetPosition() { return body.getPosition(); }
	vec2 GetHalfSize() { return body.getPosition() / 2.0f; }

private:
	
};

