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

	void DrawRect(float x, float y, float width, float height);

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};
