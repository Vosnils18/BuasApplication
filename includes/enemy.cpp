#include "enemy.h"
#include "../surface.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;

Enemy::Enemy(Sprite* spriteIdle, Sprite* spriteRun)
{
	this->spriteIdle = spriteIdle;
	this->spriteRun = spriteRun;
	this->spriteIdle = spriteIdle;

	this->position = position;

	this->speed = 5.0f;
	this->width = 16;
	this->height = 16;
	
	this->enemyMoveTimer = 0;
	this->direction = 1;
	
	this->running = 0;
	this->lookingLeft = false;
	this->animationFrame = 1;

	srand(static_cast<unsigned int>(time(0)));
}

void Enemy::setPosition(vec2 pos)
{
	position = pos;
}

void Enemy::Update()
{
	if (enemyMoveTimer < 1)
	{
		direction = (rand() % 8) + 1;
		enemyMoveTimer += rand() % 40 + 5;
	}
	else if (enemyMoveTimer >= 1)
	{
		enemyMoveTimer--;
	}

	if (direction == 1) { position.x--; running = true; lookingLeft = true; }
	else if (direction == 2) { position.x++; running = true; lookingLeft = false; }
	else if (direction == 3) { position.y--; running = true; }
	else if (direction == 4) { position.y++; running = true; }
	else { running = false; }
	//std::cout << running << " " << direction << std::endl;

	if (running == true)
	{
		activeSprite = spriteRun;
	}
	else if (running == false)
	{
		activeSprite = spriteIdle;
	}

	if (!lookingLeft)
	{
		if (animationFrame < 39)
		{
			animationFrame++;
		}
		else
		{
			animationFrame = 1;
		}
	}
	else
	{
		if (animationFrame < 79 && animationFrame > 39)
		{
			animationFrame++;
		}
		else
		{
			animationFrame = 40;
		}
	}

	activeSprite->SetFrame(animationFrame / 10);

	if (position.x < 16) { position.x = 16; }
	if (position.x > BufferWidth - 16 - width) { position.x = BufferWidth - 16 - width; }
	if (position.y < 16 - 5) { position.y = 16 - 5; }
	if (position.y > BufferHeight - 16 - height) { position.y = BufferHeight - 16 - height; }
}

void Enemy::Draw(Tmpl8::Surface* screen)
{
	activeSprite->Draw(screen, position.x, position.y);
}