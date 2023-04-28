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
#include "includes/ui.h"

constexpr int FULLHP = 6;

namespace Tmpl8
{
	//Create Sprites and background
	Surface background("assets/theRealOne/Level_0.png");
	
	Sprite* playerSpriteIdle(new Sprite(new Surface("assets/theRealOne/Wizard_run.png"), 8));
	Sprite* playerSpriteRun(new Sprite(new Surface("assets/theRealOne/Wizard_idle.png"), 8));
	Sprite* playerSpriteIdleRed(new Sprite(new Surface("assets/theRealOne/Wizard_run_Red.png"), 8));
	Sprite* playerSpriteRunRed(new Sprite(new Surface("assets/theRealOne/Wizard_idle_Red.png"), 8));
	
	Sprite* bulletSprite(new Sprite(new Surface("assets/theRealOne/Bullet.png"), 2));
	Sprite* heartSprite(new Sprite(new Surface("assets/theRealOne/Hearts.png"), 3));
	
	Sprite* enemySpriteIdle(new Sprite(new Surface("assets/theRealOne/Imp_idle.png"), 8));
	Sprite* enemySpriteRun(new Sprite(new Surface("assets/theRealOne/Imp_run.png"), 8));
	
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<Heart*> hearts;
	int counter = 10;

	//Mouse state
	float Game::mx = 0;
	float Game::my = 0;
	bool Game::mouseClicked = false;
	int attackTimer = 0;

	//Create player
	Player player(playerSpriteIdle, playerSpriteIdleRed, playerSpriteRun, playerSpriteRunRed);

	int currentScore;
	int gameState;

	void Game::Init(SDL_Window* win)
	{
		window = win;
		gameState = 0;
		srand(static_cast<unsigned int>(time(0)));

		//Create enemies
		for (size_t i = 0; i < counter; i++)
		{
			enemies.emplace_back(new Enemy(enemySpriteIdle, enemySpriteRun));
			vec2 randomNumber = vec2((rand() % (BufferWidth - 16)) + 16, (rand() % (BufferHeight - 16)) + 16);
			enemies[i]->setPosition(randomNumber);
		}
		
		for (size_t i = 0; i < FULLHP / 2; i++)
		{
			hearts.emplace_back(new Heart(heartSprite));
		}

		currentScore = 0;
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
		for (size_t i = 0; i < hearts.size(); i++)
		{
			delete hearts[i];
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
		switch (gameState)
		{
		case 0:
			gameState = 1;
			std::cout << "0 to 1" << std::endl;
			break;

		case 1:
		{
			background.CopyTo(screen, 0, 0);

			//Mouse position and calculating normalised aim direction.
			vec2 mousePos = vec2(mx, my);
			vec2 aimDir = mousePos - player.position;
			vec2 aimDirNorm = aimDir.normalized();

			//give velocity to bullet when clicked and put bullet object in bullet vector.
			if (mouseClicked)
			{
				if (attackTimer == 0)
				{
					bullets.emplace_back(new Bullet(bulletSprite, player.position, mousePos, aimDirNorm));
					attackTimer += 15;
				}
			}
			if (attackTimer > 0)
			{

				attackTimer = attackTimer - 1 * (deltaTime / 10);
			}

			//Move entities while checking collision with others, then draw them to the screen.
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i]->Update();
				for (size_t j = 0; j < bullets.size(); j++)
				{
					if (enemies[i]->GetCollider().CheckCollision(bullets[j]->GetCollider(), 1.0f))
					{
						bullets[j]->destroy = true;
						enemies[i]->destroy = true;
					}
				}

				if (enemies[i]->GetCollider().CheckCollision(player.GetCollider(), 2.0f))
				{
					player.DealDamage(1);
				}

				enemies[i]->Draw(screen);
			}

			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i]->Move(screen);
			}

			player.Update();
			player.Draw(screen);

			for (size_t i = 0; i < hearts.size(); i++)
			{
				hearts[i]->Update(player.health, i);
				hearts[i]->Draw(screen);
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
					currentScore++;
					std::cout << "Your score: " << currentScore << std::endl;
					return true;
				}
				return false;
			};
			enemies.erase(std::remove_if(enemies.begin(), enemies.end(), deleteDestroyedEnemy), enemies.end());

			if (player.health <= 0)
			{
				gameState = 2;
			}
			break;
		}
		case 2:
		{
			screen->Clear(30);

			int boxWidth = 100;
			int boxHeight = 50;

			int BoxX1 = (BufferWidth / 2) - (boxWidth / 2);
			int BoxY1 = (BufferHeight / 2) - (boxHeight / 2);

			int tx = BoxX1 + (boxWidth - 6 * strlen("Game Over")) / 2.0 + 1;
			int ty = BoxY1 + (boxHeight - 6) / 2.0;

			screen->Bar(BoxX1, BoxY1, BoxX1 + boxWidth, BoxY1 + boxHeight, 0);
			screen->Print("Game Over", tx, ty, 255);
			
			std::cout << gameState << std::endl;
			break;
		}
		}
	}
};