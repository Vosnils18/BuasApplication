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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


namespace Tmpl8
{
	//Create Sprites and background
	Surface background("assets/theRealOne/Level_0.png");
	Sprite* playerSprite(new Sprite(new Surface("assets/theRealOne/imp_idle_anim_f0.png"), 1));
	Sprite* bulletSprite(new Sprite (new Surface("assets/theRealOne/Bullet.png"), 2));


	float Game::mx = 0;
	float Game::my = 0;
	bool Game::mouseClicked = false;

	//Surface tiles("assets/theRealOne/TileSheet_DungeonPurple.png");
	//char map[TILEROWS][TILECOLUMNS*TILEROWS];
	//char backWalls[5] = { 'caX', 'gcX', 'gdX', 'caX', 'caX' };

	void Game::Init(SDL_Window* win)
	{
		window = win;

		//srand(static_cast<unsigned int>(time(0)));
		//int random = rand() %5;
		//for (int i = 0; i < TILEROWS; i++)
		//{
		//	map[i][1] = 'baX';
		//	for (int j = 1; j < TILECOLUMNS -1; j++)
		//	{
		//		map[i][j] = backWalls[random];
		//	}
		//	map[i][TILECOLUMNS] = 'faX';
		//}
	}

	void Game::Shutdown()
	{

	}


	//void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	//{
	//	Pixel* src = tiles.GetBuffer() + 1 + tx * 16 + (1 + ty * 16) * 112;
	//	Pixel* dst = screen->GetBuffer() + x + y * BufferWidth;
	//	for (int i = 0; i < TILESIZE; i++, src += 112, dst += BufferWidth)
	//		for (int j = 0; j < TILESIZE; j++)
	//			dst[j] = src[j];
	//}


	void Game::MouseMove(int x, int y)
	{
		/* Store the updated mouse position */
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
		//for (int y = 0; y < TILEROWS; y++)
		//	for (int x = 0; x < TILECOLUMNS; x++)
		//	{
		//		int tx = map[y][x * 3] - 'a';
		//		int ty = map[y][x * 3 + 1] - 'a';
		//		DrawTile(tx, ty, screen, x * TILESIZE, y * TILESIZE);
		//	}
		
		//Create player
		Player player(playerSprite);

		player.Move();


		//Bullet code
		Vector2f mousePos = Vector2f(mouseF.x, mouseF.y);
		Vector2f aimDir = mousePos - player.playerPos;
		Vector2f aimDirNorm = aimDir / sqrtf(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		//Create bullet array
		Bullet bullet(bulletSprite, player.playerPos, mousePos);
		std::vector<Bullet> bullets;
		bullets.push_back(Bullet(bullet));

		//Check mouse position when lmb is clicked and give path to bullet
		if (mouseClicked)
		{
			bullet.setPosition(player.playerPos);
			bullet.setVelocity(aimDirNorm);

			bullets.push_back(Bullet(bullet));
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Move();
		}


		//enemy code


		//Draw
		background.CopyTo(screen, 0, 0);

		player.Draw(screen);

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Draw(screen);
		}
	}
};