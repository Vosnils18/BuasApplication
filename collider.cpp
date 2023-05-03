#include "collider.h"
#include "template.h"
#include <utility>

using namespace Tmpl8;

Collider::Collider(vec2 position, vec2 size)
{
	this->position = position;
	this->size = size;
}

bool Collider::CheckCollision(Collider& other)
{
	vec2 otherPosition = other.GetPosition();
	vec2 otherHalfSize = other.GetHalfSize();
	vec2 thisPosition = GetPosition();
	vec2 thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		return true;
	}
	
	return false;
}