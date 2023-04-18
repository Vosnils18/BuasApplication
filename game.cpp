#include "game.h"
#include "surface.h"
#include "template.h"

#include <cstdio> //printf
#include <cstdlib>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "includes/player.h"
#include "includes/bullet.h"
#include "includes/enemy.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


namespace Tmpl8
{
	//Create Sprites and background
	Surface background("assets/theRealOne/Level_0.png");
	Sprite* playerSprite(new Sprite(new Surface("assets/theRealOne/lizard_m_idle_anim_f0.png"), 1));
	Sprite* bulletSprite(new Sprite (new Surface("assets/theRealOne/Bullet.png"), 2));
	Sprite* enemySprite(new Sprite(new Surface("assets/theRealOne/imp_idle_anim_f0.png"), 1));

	int counter = 0;

	float Game::mx = 0;
	float Game::my = 0;
	bool Game::mouseClicked = false;

	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;

	void Game::Init(SDL_Window* win)
	{
		window = win;
	}

	void Game::Shutdown()
	{

	}

	void Game::MouseMove(int x, int y)
	{
		//Store updated mouse position
		float sx = static_cast<float>(ScreenWidth) / BufferWidth;
		float sy = static_cast<float>(ScreenHeight) / BufferHeight;

		mouseF.x += x / sx;
		mouseF.y += y / sy;

		Game::mx = mouseF.x;
		Game::my = mouseF.y;
	}
	void Game::MouseDown(int button)
	{
		if (button == 1) { Game::mouseClicked = true; }
	}
	void Game::MouseUp(int button)
	{
		if (button == 1) { Game::mouseClicked = false; }
	}

	void Game::Tick(float deltaTime)
	{
		background.CopyTo(screen, 0, 0);

		//Create player
		Player player(playerSprite);
		player.Move();


		//Bullet code
		Vector2f mousePos = Vector2f(mouseF.x, mouseF.y);
		Vector2f aimDir = mousePos - player.playerPos;
		Vector2f aimDirNorm = aimDir / sqrtf(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		//Create bullet
		Bullet bullet(bulletSprite, player.playerPos, mousePos);

		//Check mouse position when lmb is clicked and give path to bullet
		if (mouseClicked)
		{
			bullet.setVelocity(aimDirNorm);
			bullets.push_back(Bullet(bullet));
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Move(screen);
		}


		//enemy code
		Enemy enemy(enemySprite);
		enemy.setPosition();
		enemy.Move();


		//Draw
		player.Draw(screen);
		enemy.Draw(screen);

		//for (size_t i = 0; i < bullets.size(); i++)
		//{
		//	bullets[i].Draw(screen);
		//}
	}
};