#include "enemy.h"
#include "../surface.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;
constexpr int INRANGE = 50;

Enemy::Enemy(Sprite* spriteIdle, Sprite* spriteRun, int isShooter)
{
	srand(static_cast<unsigned int>(time(0)));
	this->spriteIdle = spriteIdle;
	this->spriteRun = spriteRun;
	this->spriteIdle = spriteIdle;

	this->position = position;
	this->attackTimer = rand() % 200 + 100;
	this->isShooter = isShooter;

	this->speed = 5.0f;
	this->width = 10;
	this->height = 12;
	
	this->enemyMoveTimer = 0;
	this->direction = 1;
	
	this->running = 0;
	this->lookingLeft = false;
	this->animationFrame = 1;
	this->followPlayer = false;
}

void Enemy::setPosition(vec2 pos)
{
	position = pos;
}

void Enemy::Update(float deltaTime, vec2 playerPos)
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
	
	vec2 pathToPlayer = playerPos - position;
	vec2 aimDirNorm = pathToPlayer.normalized();

	if ((-INRANGE <= pathToPlayer.x && pathToPlayer.x <= INRANGE) || (-INRANGE <= pathToPlayer.y && pathToPlayer.y <= INRANGE))
	{
		followPlayer = true;
		if (pathToPlayer.x > 0)
		{
			lookingLeft = false;
		}
		else
		{
			lookingLeft = true;
		}
		position += aimDirNorm;
	}
	else if (direction == 1) { position.x--; running = true; followPlayer = false; lookingLeft = true; }
	else if (direction == 2) { position.x++; running = true; followPlayer = false; lookingLeft = false; }
	else if (direction == 3) { position.y--; running = true; followPlayer = false; }
	else if (direction == 4) { position.y++; running = true; followPlayer = false; }
	else { running = false; followPlayer = false; }
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

	if (attackTimer > 0)
	{
		attackTimer = attackTimer - 1 * (deltaTime / 10);
	}

	positionHitBox.x = position.x + 4;
	positionHitBox.y = position.y + 3;
}

void Enemy::Draw(Tmpl8::Surface* screen)
{
	activeSprite->Draw(screen, position.x, position.y);
}