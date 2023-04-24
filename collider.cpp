#include "collider.h"
#include "template.h"
#include <utility>

using namespace Tmpl8;

Collider::Collider(vec2 position, vec2 size)
{
	this->position = position;
	this->size = size;
}

bool Collider::CheckCollision(Collider& other, float force)
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
		force - std::min(std::max(force, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX = (1.0f - force), 0.0f);
				other.Move(intersectX * force, 0.0f);
			}
			else
			{
				Move(intersectX = (1.0f - force), 0.0f);
				other.Move(intersectX * force, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(intersectY = 0.0f, (1.0f - force));
				other.Move(0.0f, intersectY * force);
			}
			else
			{
				Move(intersectY = 0.0f, (1.0f - force));
				other.Move(0.0f, intersectY * force);
			}
		}

		return true;
	}
	
	return false;
}