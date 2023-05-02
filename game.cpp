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
#include "includes/trapdoor.h"
#include "includes/healthflask.h"

constexpr int FULLHP = 6;

namespace Tmpl8
{
	//Create Sprites and background
	Surface background("assets/theRealOne/Level_0.png");
	
	//player sprites
	Sprite* playerSpriteIdle(new Sprite(new Surface("assets/theRealOne/Wizard_run.png"), 8));
	Sprite* playerSpriteRun(new Sprite(new Surface("assets/theRealOne/Wizard_idle.png"), 8));
	Sprite* playerSpriteIdleRed(new Sprite(new Surface("assets/theRealOne/Wizard_run_Red.png"), 8));
	Sprite* playerSpriteRunRed(new Sprite(new Surface("assets/theRealOne/Wizard_idle_Red.png"), 8));
	
	//miscellaneous sprites
	Sprite* bulletSprite(new Sprite(new Surface("assets/theRealOne/Bullet.png"), 2));
	Sprite* heartSprite(new Sprite(new Surface("assets/theRealOne/Hearts.png"), 3));
	Sprite* trapDoorSprite(new Sprite(new Surface("assets/theRealOne/Trapdoor.png"), 1));
	Sprite* healthFlaskSprite(new Sprite(new Surface("assets/theRealOne/flask_red.png"), 1));
	
	//enemy sprites
	Sprite* enemySpriteIdle(new Sprite(new Surface("assets/theRealOne/Imp_idle.png"), 8));
	Sprite* enemySpriteRun(new Sprite(new Surface("assets/theRealOne/Imp_run.png"), 8));

	//buttons
	Button* restartButton(new Button("Restart Game", 0x000000, 0xffffff));
	Button* startButton(new Button("Start Game", 0x000000, 0xffffff));
	
	//Vectors for bullets, enemies and hearts to be stored in
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<Heart*> hearts;
	std::vector<HealthFlask*> flasks;
	int counter = 5;

	//Mouse state
	float Game::mx = 0;
	float Game::my = 0;
	bool Game::mouseClicked = false;

	//Create player
	Player player(playerSpriteIdle, playerSpriteIdleRed, playerSpriteRun, playerSpriteRunRed);

	TrapDoor* trapdoor;

	int currentScore;
	int floorLevel;
	int gameState;

	Score score(currentScore);

	void Game::Init()
	{
		gameState = 0;
	}

	void Game::Start()
	{
		CreateEnemies(counter);

		//set player health and position
		player.health = FULLHP;
		player.position = vec2(32, 32);
		for (size_t i = 0; i < FULLHP / 2; i++)
		{
			hearts.emplace_back(new Heart(heartSprite));
		}

		currentScore = 0;
		trapdoor = new TrapDoor(trapDoorSprite);
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
		delete trapdoor;

		delete playerSpriteIdle;
		delete playerSpriteIdleRed;
		delete playerSpriteRun;
		delete playerSpriteRunRed;
		delete trapDoorSprite;
		delete heartSprite;
		delete healthFlaskSprite;
		delete enemySpriteIdle;
		delete enemySpriteRun;
		delete bulletSprite;
	}

	//function is called every time mouse moves. Saves mouse coordinates oin mx, my
	void Game::MouseMove(int x, int y)
	{
		float sx = static_cast<float>(ScreenWidth) / BufferWidth;
		float sy = static_cast<float>(ScreenHeight) / BufferHeight;

		Game::mx += x / sx;
		Game::my += y / sy;
	}
	//funcions called when mouse is clicked and released, updates mouseClicked bool
	void Game::MouseDown(int button)
	{
		if (button == 1) { Game::mouseClicked = true; }
	}
	void Game::MouseUp(int button)
	{
		if (button == 1) { Game::mouseClicked = false; }
	}

	void Game::CreateEnemies(int counter)
	{
		//put random numbers in 2 different arrays for the x and y coordinates of every enemy to be pulled from
		srand(static_cast<unsigned int>(time(0)));
		int* randomNumbersX = new int[counter];
		int* randomNumbersY = new int[counter];
		for (size_t i = 0; i < counter; i++)
		{
			randomNumbersX[i] = rand() % (BufferWidth - 16) + 16;
			randomNumbersY[i] = rand() % (BufferHeight - 16) + 16;
		}

		//create enemies and place them in vector
		for (size_t i = 0; i < counter; i++)
		{
			enemies.emplace_back(new Enemy(enemySpriteIdle, enemySpriteRun, i));
			enemies[i]->setPosition(vec2(randomNumbersX[i], randomNumbersY[i]));
		}
		delete randomNumbersX;
		delete randomNumbersY;
	}

	//function called on restart, deletes all existing objects
	void Game::Reset()
	{
		counter = 5;
		delete trapdoor;

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->destroy = true;
		}
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i]->destroy =true;
		}
		for (size_t i = 0; i < flasks.size(); i++)
		{
			flasks[i]->destroy = true;
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

		// delete and remove destroyed healthFlasks from vector
		auto deleteDestroyedFlask = [](HealthFlask* f)
		{
			if (f->destroy)
			{
				delete f;
				return true;
			}
			return false;
		};
		flasks.erase(std::remove_if(flasks.begin(), flasks.end(), deleteDestroyedFlask), flasks.end());

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

		auto deleteDestroyedHeart = [](Heart* h)
		{
			delete h;
			return true;
		};
		hearts.erase(std::remove_if(hearts.begin(), hearts.end(), deleteDestroyedHeart), hearts.end());
	}

	void Game::NextLevel(float deltaTime)
	{
		player.invincibilityTimer = 3 * deltaTime;
		trapdoor->SetPosition();
		player.position = player.position;
		
		for (size_t i = 0; i < flasks.size(); i++)
		{
			flasks[i]->destroy = true;
		}
		
		counter = counter + 2;
		floorLevel--;
		
		CreateEnemies(counter);
	}
	


	void Game::Tick(float deltaTime)
	{
		switch (gameState)
		{
		case 0:
			screen->Clear(255);
			startButton->Create(screen, vec2(300, 350));
			if (startButton->CheckPosition(vec2(mx, my), mouseClicked))
			{
				Start();
				gameState = 1;
				floorLevel = 0;
			}
			break;

		case 1:
		{
			background.CopyTo(screen, 0, 0);

			//Mouse position
			vec2 mousePos = vec2(mx, my);

			//give velocity to bullet when clicked and put bullet object in bullet vector.
			if (mouseClicked)
			{
				if (player.attackTimer == 0)
				{
					bullets.emplace_back(new Bullet(bulletSprite, player.position, mousePos, false));
					player.attackTimer += 2 * deltaTime;
				}
			}

			//Move enemies while checking collision with others, then draw them to the screen.
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i]->Update(deltaTime, player.position);
				
				for (size_t j = 0; j < bullets.size(); j++)
				{
					//check collision between bullets and enemies, and if true, destroy both
					if (enemies[i]->GetCollider().CheckCollision(bullets[j]->GetCollider(), 1.0f) && !bullets[j]->enemyBullet)
					{
						bullets[j]->destroy = true;
						enemies[i]->destroy = true;
					}
				}

				//check collision between enemies and player
				if (enemies[i]->GetCollider().CheckCollision(player.GetCollider(), 2.0f))
				{
					player.DealDamage(1);
				}

				//check conditions for enemy attack and fire bullet towards player if conditions are right
				if (enemies[i]->attackTimer == 0 && enemies[i]->followPlayer && enemies[i]->isShooter % 4 == 0)
				{
					bullets.emplace_back(new Bullet(bulletSprite, enemies[i]->position, player.position, true));
					enemies[i]->attackTimer += rand() % 400 + 50;
				}

				enemies[i]->Draw(screen);
			}

			//ccheck collision between player and bullets fired by enemies
			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i]->Move(screen);
				if (bullets[i]->GetCollider().CheckCollision(player.GetCollider(), 2.0f) && bullets[i]->enemyBullet)
				{
					player.DealDamage(1);
				}
			}

			for (size_t i = 0; i < flasks.size(); i++)
			{
				if (flasks[i]->GetCollider().CheckCollision(player.GetCollider(), 2.0f))
				{
					flasks[i]->destroy = true;
					if (player.health < FULLHP)
					{
						player.health++;
					}
				}
				flasks[i]->Draw(screen);
			}

			player.Update(deltaTime);
			player.Draw(screen);
			score.Update(currentScore, screen, vec2(BufferWidth -120, 20));
			score.Floor(floorLevel, screen);


			for (size_t i = 0; i < hearts.size(); i++)
			{
				hearts[i]->Update(player.health, i);
				hearts[i]->Draw(screen);
			}

			// delete and remove destroyed bullets from vector
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

			// delete and remove destroyed healthFlasks from vector
			auto deleteDestroyedFlask = [](HealthFlask* f)
			{
				if (f->destroy)
				{
					delete f;
					return true;
				}
				return false;
			};
			flasks.erase(std::remove_if(flasks.begin(), flasks.end(), deleteDestroyedFlask), flasks.end());

			// delete and remove destroyed enemies from vector
			auto deleteDestroyedEnemy = [](Enemy* e)
			{
				if (e->destroy)
				{
					if (e->dropsHeart())
					{
						flasks.emplace_back(new HealthFlask(healthFlaskSprite, e->position));
					}
					delete e;
					currentScore++;
					std::cout << "Your score: " << currentScore << std::endl;
					return true;
				}
				return false;
			};
			enemies.erase(std::remove_if(enemies.begin(), enemies.end(), deleteDestroyedEnemy), enemies.end());

			//advance to next level when all enemies have been defeated
			if (enemies.size() < 1)
			{
				trapdoor->Draw(screen);

				if (trapdoor->GetCollider().CheckCollision(player.GetCollider(), 0.0f))
				{
					NextLevel(deltaTime);
				}
			}

			//end game if player health reaches 0
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
			
			score.Update(currentScore, screen, vec2(tx, ty - 100));
			score.Floor(floorLevel, screen);

			restartButton->Create(screen, vec2(BoxX1, BoxY1 + (boxHeight * 2)));
			if (restartButton->CheckPosition(vec2(mx, my), mouseClicked))
			{
				Reset();
				gameState = 0;
			}
			break;
		}
		}
	}
};