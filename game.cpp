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


namespace Tmpl8
{
	//Create Sprites and background
	Surface background("assets/theRealOne/Level_0.png");
	Sprite* playerSprite(new Sprite(new Surface("assets/theRealOne/lizard_m_idle_anim_f0.png"), 1));
	Sprite* bulletSprite(new Sprite (new Surface("assets/theRealOne/Bullet.png"), 2));
	Sprite* enemySprite(new Sprite(new Surface("assets/theRealOne/imp_idle_anim_f0.png"), 1));
	
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	int counter = 3;

	//Mouse state
	float Game::mx = 0;
	float Game::my = 0;
	bool Game::mouseClicked = false;


	void Game::Init(SDL_Window* win)
	{
		window = win;

		//Create enemy
		for (size_t i = 0; i < counter; i++)
		{
			enemies.emplace_back(new Enemy(enemySprite));
		}
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

		////Create enemy
		//for (size_t i = 0; i < counter; i++)
		//{
		//	enemies.emplace_back(enemySprite);
		//}

		//Mouse position and calculating normalised aim direction.
		vec2 mousePos = vec2(mouseF.x, mouseF.y);
		vec2 aimDir = mousePos - player.playerPos;
		vec2 aimDirNorm = aimDir / sqrtf(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		//Create bullet
		//Bullet bullet(bulletSprite, player.playerPos, mousePos);

		//give velocity to bullet when clicked and put bullet object in bullet vector.
		if (mouseClicked)
		{
			bullets.push_back(new Bullet(bulletSprite, player.playerPos, mousePos));
		}

		//Move and draw entities
		player.Move();
		player.Draw(screen);
		for (size_t i = 0; i < counter; i++)
		{
			enemies[i]->Move();
			//enemies[i].GetCollider().CheckCollision(bullet.GetCollider(), 0.0f);
			enemies[i]->Draw(screen);
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Move(screen);
		}
	}
};