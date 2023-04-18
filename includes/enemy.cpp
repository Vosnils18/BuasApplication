#include "enemy.h"
#include "../surface.h"
#include "../game.h"
#include "../template.h"

using sf::Vector2f;
using Tmpl8::Sprite;

Enemy::Enemy(Sprite* sprite)
{
	this->sprite = sprite;
	this->position = position;
	this->speed = 5.0f;
	this->width = sprite->GetWidth();
	this->height = sprite->GetHeight();

	srand(static_cast<unsigned int>(time(0)));
}

void Enemy::setPosition()
{
	Vector2f randomPosition = Vector2f((rand() % (BufferWidth - 16)) + 16, (rand() % (BufferHeight - 16)) + 16);
	position = randomPosition;
}

void Enemy::Move()
{
	int direction = (rand() % 4) + 1;

	if (direction == 1 ) position.x--;
	if (direction == 2 ) position.x++;
	if (direction == 3 ) position.y--;
	if (direction == 4 ) position.y++;

	if (position.x < 16) { position.x = 16; }
	if (position.x > BufferWidth - 16 - width) { position.x = BufferWidth - 16 - width; }
	if (position.y < 16 - 5) { position.y = 16 - 5; }
	if (position.y > BufferHeight - 16 - height) { position.y = BufferHeight - 16 - height; }
}

void Enemy::Draw(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, position.x, position.y);
}