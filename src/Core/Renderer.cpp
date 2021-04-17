#include "Renderer.hpp"
#include "UI.hpp"
#include <iostream>

const int MET2PIX = 32;
const vec3 COLOR_SCREEN_BG = vec3(69, 82, 108);
const vec3 COLOR_DYNAMIC = vec3(248, 245, 241);
const vec3 COLOR_STATIC = vec3(90, 168, 151);
const vec3 COLOR_SENSOR = vec3(248, 164, 136);

Renderer::Renderer()
	:m_Window(nullptr)
	,m_Renderer(nullptr)
{

}

Renderer::~Renderer()
{

}

bool Renderer::Initialize(int screenWidth, int screenHeight)
{
	m_Window = SDL_CreateWindow("Strong Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, NULL);
	if (!m_Window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_Renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	TTF_Quit();
}

void Renderer::Clear()
{
	SDL_SetRenderDrawColor(m_Renderer, COLOR_SCREEN_BG.x, COLOR_SCREEN_BG.y, COLOR_SCREEN_BG.z, 255);
	SDL_RenderClear(m_Renderer);
}

void Renderer::Present()
{
	SDL_RenderPresent(m_Renderer);
}

void Renderer::DrawRect(float x, float y, float width, float height, Camera& camera, vec3 color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.x, color.y, color.z, 255);

	unsigned int pixelPerMetre = camera.GetPixelPerMetre();
	vec2 position = camera.GetPosition();

	SDL_Rect rect {
		static_cast<int>(x * pixelPerMetre - position.x),
		static_cast<int>(y * pixelPerMetre - position.y),
		static_cast<int>(width * pixelPerMetre),
		static_cast<int>(height * pixelPerMetre)
	};

	SDL_RenderFillRect(m_Renderer, &rect);
}

void Renderer::DrawBody(b2Body* body, Camera& camera)
{
	b2Fixture* fixture = body->GetFixtureList();
	b2Vec2 position = body->GetPosition();

	while (fixture)
	{
	 	b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
		float width = shape->m_vertices[1].x - shape->m_vertices[0].x;
		float height = shape->m_vertices[2].y - shape->m_vertices[0].y;
		float x = (position.x - (width / 2) + shape->m_centroid.x);
		float y = (position.y - (height / 2) + shape->m_centroid.y);

 		if (fixture->IsSensor())
		{
			DrawRect(x, y, width, height, camera, COLOR_SENSOR);
		}
		else if (body->GetType() == b2_dynamicBody)
		{
			DrawRect(x, y, width, height, camera, COLOR_DYNAMIC);
		}
		else
		{
			DrawRect(x, y, width, height, camera, COLOR_STATIC);
		}

		fixture = fixture->GetNext();
	}
}
