#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>

#include "template.h"

using std::shared_ptr;
using std::unique_ptr;

namespace Tmpl8 {

	constexpr float TILESIZE = 16;

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
	void Init();
	void Start();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);
	void KeyUp(int key){}
	void KeyDown(int key){}
	void Reset();
	void NextLevel();
private:
	/* windowing */
	Surface* screen = nullptr;
	SDL_Window* window = nullptr;

	unsigned long frame = 0u;
	vec2 mouseF;
};

}; // namespace Tmpl8