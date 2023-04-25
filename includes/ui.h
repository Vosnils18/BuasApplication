#pragma once

#include "../surface.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;

class Heart
{
public:
	Heart(Sprite* sprite);

	void Update(int health);

	void Draw(Surface* screen);

private:
	Sprite* sprite = nullptr;
	vec2 position;

	int health;
};