#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <box2d/box2d.h>
#include "Camera.hpp"
#include "Math.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(int screenWidth, int screenHeight);
	void Shutdown();

	void Clear();
	void Present();

	void DrawRect(float x, float y, float width, float height, Camera& camera, vec3 color = vec3(255, 255, 255));
	void DrawBody(b2Body* body, Camera& camera);

	SDL_Renderer* GetSDLRenderer() { return m_Renderer; }

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};
