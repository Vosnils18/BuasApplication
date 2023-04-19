#pragma once
#include <SFML/Graphics.hpp>

using sf::Vector2f;

class Collider
{
public:
	Collider(sf::RectangleShape& body);

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider& other, float push);

	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getPosition() / 2.0f; }

private:
	sf::RectangleShape& body;
};

