#include "enemy.h"
#include "../surface.h"
#include "../game.h"
#include "../template.h"

using namespace Tmpl8;
constexpr int INRANGE = 70;

ImpEnemy::ImpEnemy(Sprite* spriteIdle, Sprite* spriteRun, Sprite* bouncySprite, int isShooter, bool isBouncy)
{
	srand(static_cast<unsigned int>(time(0)));
	this->spriteIdle = spriteIdle;
	this->spriteRun = spriteRun;
	this->spriteIdle = spriteIdle;
	this->bouncySprite = bouncySprite;

	this->position = position;
	this->attackTimer = rand() % 200 + 100;
	this->isShooter = isShooter;
	
	this->isBouncy = isBouncy;
	this->rage = false;

	this->speed = 1.0f;
	this->width = 12;
	this->height = 14;
	
	this->enemyMoveTimer = 0;
	this->direction = 1;
	
	this->running = 0;
	this->lookingLeft = false;
	this->animationFrame = 0;

	if (isBouncy)
	{
		health = 2;
	}
	else
	{
		health = 1;
	}
}

void ImpEnemy::setPosition(vec2 pos)
{
	position = pos;
}

void ImpEnemy::Update(float deltaTime, vec2 playerPos)
{
	if (isBouncy)
	{
		activeSprite = bouncySprite;

		if (rage)
		{
			if (position.x < TILESIZE) { currentv.x -= currentv.x * 2; }
			if (position.x > BufferWidth - TILESIZE - width) { currentv.x -= currentv.x * 2; }
			if (position.y < TILESIZE - 5) { currentv.y -= currentv.y * 2; }
			if (position.y > BufferHeight - TILESIZE - height) { currentv.y -= currentv.y * 2; }
			
			position += currentv;
		}
		else 
		{
			if (enemyMoveTimer < 1)
			{
				direction = (rand() % 4) + 1;
				enemyMoveTimer += rand() % 40 + 5;
			}
			else if (enemyMoveTimer >= 1)
			{
				enemyMoveTimer--;
			}

			if (direction == 1) { position.x--; running = true; followPlayer = false; lookingLeft = true; }
			else if (direction == 2) { position.x++; running = true; followPlayer = false; lookingLeft = false; }
			else if (direction == 3) { position.y--; running = true; followPlayer = false; }
			else if (direction == 4) { position.y++; running = true; followPlayer = false; }

			if (position.x < TILESIZE) { position.x = TILESIZE; }
			if (position.x > BufferWidth - TILESIZE - width) { position.x = BufferWidth - TILESIZE - width; }
			if (position.y < TILESIZE - 5) { position.y = TILESIZE - 5; }
			if (position.y > BufferHeight - TILESIZE - height) { position.y = BufferHeight - TILESIZE - height; }
		}

		positionHitBox.x = position.x + 3;
		positionHitBox.y = position.y + 4;

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
	}
	else
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
		currentv = aimDirNorm * speed;

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
			position += currentv;
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

		if (position.x < TILESIZE) { position.x = TILESIZE; }
		if (position.x > BufferWidth - TILESIZE - width) { position.x = BufferWidth - TILESIZE - width; }
		if (position.y < TILESIZE - 5) { position.y = TILESIZE - 5; }
		if (position.y > BufferHeight - TILESIZE - height) { position.y = BufferHeight - TILESIZE - height; }

		if (attackTimer > 0)
		{
			attackTimer = attackTimer - 1 * (deltaTime / 10);
		}

		positionHitBox.x = position.x + 3;
		positionHitBox.y = position.y + 2;
	}

	if (health <= 0)
	{
		destroy = true;
	}
}

void ImpEnemy::Rage(vec2 position, vec2 playerPos)
{
	rage = true;
	speed = 4.0f;
	vec2 aimDir = playerPos - position;
	vec2 aimDirNorm = aimDir.normalized();
	currentv = aimDirNorm * speed;
}

void ImpEnemy::Draw(Tmpl8::Surface* screen)
{
	activeSprite->Draw(screen, position.x, position.y);
}
