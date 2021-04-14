#pragma once

#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include "Camera.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(int screenWidth, int screenHeight);
	void Shutdown();

	void Clear();
	void Present();

	void DrawRect(float x, float y, float width, float height, Camera& camera, b2Vec3 color = b2Vec3(255, 255, 255));
	void DrawBody(b2Body* body, Camera& camera);

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};
