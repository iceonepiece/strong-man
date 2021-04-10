#include "Game.hpp"

Game::Game()
	:m_Running(true)
	,m_Window(nullptr)
	,m_Renderer(nullptr)
{}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("Strong Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, NULL);
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

	m_TicksCount = SDL_GetTicks();

	return true;
}

void Game::Run()
{
	while (m_Running)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_Running = false;
				break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_Running = false;
	}

	// DO SOMETHING HERE
}

void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 16));

	float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	m_TicksCount = SDL_GetTicks();

	// DO SOMETHING HERE
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	// DO SOMETHING HERE

	SDL_RenderPresent(m_Renderer);
}
