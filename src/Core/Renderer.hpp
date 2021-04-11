#pragma once

#include <SDL2/SDL.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(int screenWidth, int screenHeight);
	void Shutdown();

	void Clear();
	void Present();

	void DrawRect(int x, int y, int width, int height);

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};
