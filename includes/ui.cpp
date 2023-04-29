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


Button::Button(char* text, Pixel buttonColor, Pixel textColor)
{
	this->position = position;
	this->buttonColor = buttonColor;
	this->textColor = textColor;
	this->text = text;
}

void Button::Create(Surface* screen, vec2 position)
{
	this->position = position;
	boxWidth = 100;
	boxHeight = 50;

	int tx = position.x + (boxWidth - 6 * strlen(text)) / 2.0 + 1;
	int ty = position.y + (boxHeight - 6) / 2.0;

	screen->Bar(position.x, position.y, position.x + boxWidth, position.y + boxHeight, buttonColor);
	screen->Print(text, tx, ty, textColor);
}

bool Button::CheckPosition(vec2 mousePos)
{
	if (mousePos.x > position.x && mousePos.x < (position.x + boxWidth))
	{
		if (mousePos.y > position.y && mousePos.y < (position.y + boxHeight))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}