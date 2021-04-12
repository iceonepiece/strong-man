#pragma once

#include <SDL2/SDL.h>
#include <box2d/box2d.h>

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
	void DrawBody(b2Body* body);

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};
