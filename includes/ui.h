#pragma once

#include "../surface.h"
#include "../game.h"
#include "../template.h"
#include "../collider.h"

using namespace Tmpl8;

class Heart
{
public:
	Heart(Sprite* sprite);

	void Update(int health, int i);

	void Draw(Surface* screen);

private:
	Sprite* sprite = nullptr;
	vec2 position;
};

class Score
{
public:
	Score(int score);

	void Update(int score);

private: 
	Font* font = nullptr;
	int score;
};

class Button
{
public: 
	Button(char* text, Pixel buttonColor, Pixel textColor);

	void Create(Surface* screen, vec2 position);

	bool CheckPosition(vec2 mousePos);

private:
	int boxWidth;
	int boxHeight;

	vec2 position;
	char* text;
	Pixel buttonColor;
	Pixel textColor;
};