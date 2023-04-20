#pragma once
#include "../template.h"

using namespace Tmpl8;

class Collider
{
public:
	Collider(vec2 position, vec2 size);

	void Move(float dx, float dy) { position = (dx, dy); }

	bool CheckCollision(Collider& other, float force);

	vec2 GetPosition() { return position; }
	vec2 GetHalfSize() { return vec2(position.x / 2.0f, position.y / 2.0f); }

private:
	vec2 position;
	vec2 size;
};

