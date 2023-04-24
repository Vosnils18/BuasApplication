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
	int attackTimer = 0;


	void Game::Init(SDL_Window* win)
	{
		window = win;

		//Create enemies
		for (size_t i = 0; i < counter; i++)
		{
			enemies.emplace_back(new Enemy(enemySprite));
		}
	}

	void Game::Shutdown()
	{
		for (size_t i = 0; i < bullets.size(); i++)
		{
			delete bullets[i];
		}
		for (size_t i = 0; i < enemies.size(); i++)
		{
			delete enemies[i];
		}
	}

	void Game::MouseMove(int x, int y)
	{
		//Store updated mouse position
		float sx = static_cast<float>(ScreenWidth) / BufferWidth;
		float sy = static_cast<float>(ScreenHeight) / BufferHeight;

		Game::mx += x / sx;
		Game::my += y / sy;
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

		//Mouse position and calculating normalised aim direction.
		vec2 mousePos = vec2(mx, my);
		vec2 aimDir = mousePos - player.playerPos;
		vec2 aimDirNorm = aimDir.normalized();

		//give velocity to bullet when clicked and put bullet object in bullet vector.
		if (mouseClicked)
		{
			std::cout << "attack!" << attackTimer << std::endl;
			if (attackTimer == 0)
			{
				bullets.emplace_back(new Bullet(bulletSprite, player.playerPos, mousePos, aimDirNorm));
				attackTimer += 7;
			}
		}
		if (attackTimer > 0)
		{
			attackTimer--;
		}

		//Move and draw entities
		player.Move();
		player.Draw(screen);
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Move();
			for (size_t j = 0; j < bullets.size(); j++)
			{
				if (enemies[i]->GetCollider().CheckCollision(bullets[j]->GetCollider(), 1.0f))
				{
					bullets[j]->destroy = true;
					enemies[i]->destroy = true;
				}
			}
			enemies[i]->Draw(screen);
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Move(screen);
		}

		// Remove deleted bullets.
		auto deleteDestroyedBullet = [](Bullet* b)
		{
			if (b->destroy)
			{
				delete b;
				return true;
			}
			return false;
		};
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), deleteDestroyedBullet), bullets.end());

		// Remove deleted enemies.
		auto deleteDestroyedEnemy = [](Enemy* e)
		{
			if (e->destroy)
			{
				delete e;
				return true;
			}
			return false;
		};
		enemies.erase(std::remove_if(enemies.begin(), enemies.end(), deleteDestroyedEnemy), enemies.end());
	}
};