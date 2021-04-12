#include "Renderer.hpp"
#include <iostream>

const int MET2PIX = 32;
const b2Vec3 COLOR_SCREEN_BG = b2Vec3(69, 82, 108);
const b2Vec3 COLOR_DYNAMIC = b2Vec3(248, 245, 241);
const b2Vec3 COLOR_STATIC = b2Vec3(90, 168, 151);
const b2Vec3 COLOR_SENSOR = b2Vec3(248, 164, 136);

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

	return true;
}

void Renderer::Shutdown()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
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

void Renderer::DrawRect(float x, float y, float width, float height, b2Vec3 color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.x, color.y, color.z, 255);

	SDL_Rect rect {
		static_cast<int>(x * MET2PIX),
		static_cast<int>(y * MET2PIX),
		static_cast<int>(width * MET2PIX),
		static_cast<int>(height * MET2PIX)
	};

	SDL_RenderFillRect(m_Renderer, &rect);
}

void Renderer::DrawBody(b2Body* body)
{
	b2Fixture* fixture = body->GetFixtureList();
	b2Vec2 position = body->GetPosition();

	while (fixture)
	{
	 	b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
		float width = shape->m_vertices[1].x - shape->m_vertices[0].x;
		float height = shape->m_vertices[2].y - shape->m_vertices[0].y;
		float x = position.x - (width / 2);
		float y = position.y - (height / 2);

 		if (fixture->IsSensor())
		{
			DrawRect(x, y, width, height, COLOR_SENSOR);
		}
		else if (body->GetType() == b2_dynamicBody)
		{
			DrawRect(x, y, width, height, COLOR_DYNAMIC);
		}
		else
		{
			DrawRect(x, y, width, height, COLOR_STATIC);
		}

		fixture = fixture->GetNext();
	}
}
