#include "player.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace Tmpl8;

constexpr int FULLHP = 6;
constexpr float MOVESPEED = 1.2;

Player::Player(Sprite* spriteIdle, Sprite* spriteIdleRed, Sprite* spriteRun, Sprite* spriteRunRed)
{
	this->spriteIdle = spriteIdle;
	this->spriteIdleRed = spriteIdleRed;
	this->spriteRun = spriteRun;
	this->spriteRunRed = spriteRunRed;
	this->activeSprite = spriteIdle;

	this->animationFrame = 1;
	this->lookingLeft = false;
	this->running = false;

	width = activeSprite->GetWidth();
	height = activeSprite->GetHeight();
	
	this->position = vec2(32, 32);
	this->health = FULLHP;
	this->invincibilityTimer = 0;
}

void Player::Update()
{
	if (running)
	{
		if (invincibilityTimer > 0)
		{
			activeSprite = spriteRunRed;
			invincibilityTimer--;
		}
		else
		{
			activeSprite = spriteRun;
		}
		std::cout << "Running" << std::endl;
	}
	else
	{
		if (invincibilityTimer > 0)
		{
			activeSprite = spriteIdleRed;
			invincibilityTimer--;
		}
		else
		{
			activeSprite = spriteIdle;
		}
		std::cout << "Idle" << std::endl;
	}

	if ((GetAsyncKeyState('W')) || (GetAsyncKeyState('A')) || (GetAsyncKeyState('S')) || (GetAsyncKeyState('D')))
	{
		running = true;
		if (GetAsyncKeyState('A')) { position.x = position.x - MOVESPEED; lookingLeft = true; }
		if (GetAsyncKeyState('D')) { position.x = position.x + MOVESPEED; lookingLeft = false; }
		if (GetAsyncKeyState('W')) { position.y = position.y - MOVESPEED; }
		if (GetAsyncKeyState('S')) { position.y = position.y + MOVESPEED; }
	}
	else { running = false; }


	activeSprite->SetFrame(animationFrame / 10);
	
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

	if (position.x < 16) { position.x = 16; }
	if (position.x > BufferWidth - 16 - width) { position.x = BufferWidth - 16 - width; }
	if (position.y < 16 - 5) { position.y = 16 - 5; }
	if (position.y > BufferHeight - 16 - height) { position.y = BufferHeight - 16 - height; }
}

void Player::Draw(Tmpl8::Surface* screen)
{
	activeSprite->Draw(screen, position.x, position.y);
}

void Player::DealDamage(int damage)
{
	if (invincibilityTimer < 1)
	{
		health -= damage;
		invincibilityTimer += 50;
	}
}