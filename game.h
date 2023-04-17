#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using std::shared_ptr;
using std::unique_ptr;
using sf::Vector2f;

namespace Tmpl8 {

	constexpr float TILESIZE = 16;
	constexpr int TILEROWS = 30;
	constexpr int TILECOLUMNS = 30;

class Surface;
class Game
{
public:

	// C++ singleton pattern : <https://stackoverflow.com/questions/1008019/c-singleton-design-pattern>
	static shared_ptr<Game> instance() {
		static shared_ptr<Game> s{ new Game };
		return s;
	}

	/* mouse position */
	static float mx;
	static float my;
	static bool mouseClicked;

	void SetTarget( Surface* surface ) { screen = surface; }
	void Init(SDL_Window* win);
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);
	void KeyUp(int key){}
	void KeyDown(int key){}
private:
	/* windowing */
	Surface* screen = nullptr;
	SDL_Window* window = nullptr;

	unsigned long frame = 0u;
	Vector2f mouseF;
};

}; // namespace Tmpl8