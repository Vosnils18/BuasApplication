#pragma once
#include "../surface.h"
#include "../collider.h"

using namespace Tmpl8;

class TrapDoor
{
public:
	TrapDoor(Sprite* Sprite);

	void SetPosition();

	void Draw(Surface* screen);

	Collider GetCollider()
	{
		return Collider(position, vec2(width, height));
	}

private:
	Sprite* sprite = nullptr;
	vec2 position;
	int width, height;
};