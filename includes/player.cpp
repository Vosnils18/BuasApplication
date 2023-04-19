#include "player.h"
#include "../template.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

float x = 32;
float y = 32;

using namespace Tmpl8;

Player::Player(Sprite* sprite)
{
	this->sprite = sprite;
	width = sprite->GetWidth();
	height = sprite->GetHeight();
	this->playerPos = vec2(x, y);
}

void Player::Move()
{
	if (GetAsyncKeyState('A')) x--;
	if (GetAsyncKeyState('D')) x++;
	if (GetAsyncKeyState('W')) y--;
	if (GetAsyncKeyState('S')) y++;

	if (x < 16) { x = 16; }
	if (x > BufferWidth - 16 - width) { x = BufferWidth - 16 - width; }
	if (y < 16 - 5) { y = 16 - 5; }
	if (y > BufferHeight - 16 - height) { y = BufferHeight - 16 - height; }
}

void Player::Draw(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, x, y);
}