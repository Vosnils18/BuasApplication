#include "ui.h"

Heart::Heart(Sprite* sprite)
{
	this->sprite = sprite;
	this->position = position;
}

void Heart::Update(int health, int i)
{
	float healthF = health / 2.0f;
	float iF = i + 1.0f;
	position = vec2(32 + (16 * (i -1)), 8);

	if (healthF >= iF)
	{
		sprite->SetFrame(0);
	}
	else if (healthF < iF && healthF > iF - 1.0f)
	{
		sprite->SetFrame(1);
	}
	else
	{
		sprite->SetFrame(2);
	}

}

void Heart::Draw(Surface* screen)
{
	sprite->Draw(screen, position.x, position.y);
}