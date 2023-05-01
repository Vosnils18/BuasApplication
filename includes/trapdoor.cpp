#include "trapdoor.h"
#include "../template.h"
#include "../game.h"

using namespace Tmpl8;

TrapDoor::TrapDoor(Sprite* sprite)
{
	this->sprite = sprite;
	this->position = position;
	this->width = 16;
	this->height = 16;

	SetPosition();
}

void TrapDoor::SetPosition()
{
	srand(static_cast<unsigned int>(time(0)));

	position.x = rand() % (BufferWidth - width * 2) + width;
	position.y = rand() % (BufferHeight - height * 2) + height;
	std::cout << position.x << " " << position.y << std::endl;
}

void TrapDoor::Draw(Surface* screen)
{
	sprite->Draw(screen, position.x, position.y);
}