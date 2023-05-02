#pragma once
#include "../surface.h"
#include "../template.h"
#include "../collider.h"

using namespace Tmpl8;

class HealthFlask
{
public:
	HealthFlask::HealthFlask(Sprite* sprite, vec2 position);

	void Draw(Surface* screen);

	Collider GetCollider()
	{
		return Collider(position, vec2(width, height));
	}

	bool destroy;

private:
	Sprite* sprite = nullptr;

	vec2 position;
	int width, height;
};

