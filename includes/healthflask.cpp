#include "healthflask.h"

HealthFlask::HealthFlask(Sprite* sprite, vec2 position)
{
	this->sprite = sprite;
	this->position = position;
	this->width = sprite->GetWidth();
	this->height = sprite->GetHeight();

	this->destroy = false;
}

void HealthFlask::Draw(Surface* screen)
{
	sprite->Draw(screen, position.x, position.y);
}