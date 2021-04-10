#pragma once
#include "SDL2/SDL.h"

class Game
{
public:
	Game();

	bool Initialize();
	void Run();
	void Shutdown();

private:
	void ProcessInput();
	void Update();
	void Render();

	bool m_Running;
	Uint32 m_TicksCount;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};
