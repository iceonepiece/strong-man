#include "Renderer.hpp"

const int MET2PIX = 24;

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
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
}

void Renderer::Present()
{
	SDL_RenderPresent(m_Renderer);
}

void Renderer::DrawRect(float x, float y, float width, float height)
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);

	SDL_Rect rect {
		static_cast<int>(x * MET2PIX),
		static_cast<int>(y * MET2PIX),
		static_cast<int>(width * MET2PIX),
		static_cast<int>(height * MET2PIX)
	};

	SDL_RenderFillRect(m_Renderer, &rect);
}