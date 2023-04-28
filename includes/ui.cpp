#include "ui.h"

Heart::Heart(Sprite* sprite)
{
	this->sprite = sprite;
	this->position = position;
}

void Heart::Update(int health, int i)
{
	float healthF = health / 2.0f;
	float iF = i + 1.0f;
	position = vec2(32 + (16 * (i -1)), 8);

	if (healthF >= iF)
	{
		sprite->SetFrame(0);
	}
	else if (healthF < iF && healthF > iF - 1.0f)
	{
		sprite->SetFrame(1);
	}
	else
	{
		sprite->SetFrame(2);
	}

}

void Heart::Draw(Surface* screen)
{
	sprite->Draw(screen, position.x, position.y);
}

Score::Score(int score)
{
	this->score = score;
}


Button::Button(char* text, Surface* screen, Pixel buttonColor, Pixel textColor, vec2 position)
{
	this->position = position;
	this->buttonColor = buttonColor;
	this->textColor = textColor;
	this->text = text;


}

//int boxWidth = 100;
//int boxHeight = 50;
//
//int tx = position.x + (boxWidth - 6 * strlen(text)) / 2.0 + 1;
//int ty = position.y + (boxHeight - 6) / 2.0;
//
//screen->Bar(position.x, position.y, position.x + boxWidth, position.y + boxHeight, color);
//screen->Print(text, tx, ty, 0xffffff);