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

	void Update(int score, Surface* screen, vec2 position);

	void Floor(int floor, Surface* screen);

private: 
	int score;
	vec2 position;
	std::string scoreText;
	std::string floorText;
};

class Button
{
public: 
	Button(char* text, Pixel buttonColor, Pixel textColor);

	void Create(Surface* screen, vec2 position);

	bool CheckPosition(vec2 mousePos, bool mouseClicked);

private:
	int boxWidth;
	int boxHeight;

	vec2 position;
	char* text;
	Pixel defaultButtonColor;
	Pixel buttonColor;
	Pixel textColor;
};