#include "Game.hpp"
#include "Renderer.hpp"
#include "Font.hpp"
#include "Scene.hpp"
#include "Audio.hpp"

Game::Game()
	:m_Running(true)
	,m_Renderer(nullptr)
	,m_CurrentScene(nullptr)
	,m_ScreenWidth(1280)
	,m_ScreenHeight(720)
{

}

Game::~Game()
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Renderer = new Renderer();
	if (!m_Renderer->Initialize(m_ScreenWidth, m_ScreenHeight))
	{
		SDL_Log("Failed to initialize renderer");
		delete m_Renderer;
		m_Renderer = nullptr;
		return false;
	}

	m_Audio = new Audio();
	if (!m_Audio->Initialize())
	{
		SDL_Log("Failed to initialize audio");
		delete m_Audio;
		m_Audio = nullptr;
		return false;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	LoadData();

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
	UnloadData();

	m_Audio->Shutdown();
	delete m_Audio;

	m_Renderer->Shutdown();
	delete m_Renderer;
	
	SDL_Quit();
}

void Game::SetCurrentScene(std::string sceneName)
{
	auto iter = m_Scenes.find(sceneName);
	if (iter != m_Scenes.end() && iter->second != m_CurrentScene)
	{
		std::cout << "CHANGE SCENE TO: " << sceneName << std::endl;
		m_CurrentScene = iter->second;
	}
}

void Game::ProcessInput()
{
	m_Input.PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_Running = false;
				break;

			default:
				break;
		}
	}

	if (m_Input.GetKeyboardState().GetKeyState(SDL_SCANCODE_ESCAPE) == EReleased)
	{
		m_Running = false;
	}

	// DO SOMETHING HERE
	m_CurrentScene->ProcessInput(m_Input);
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
	m_CurrentScene->Update(deltaTime);
}

void Game::Render()
{
	m_Renderer->Clear();

	// DO SOMETHING HERE
	m_CurrentScene->Render(m_Renderer);

	m_Renderer->Present();
}

Font* Game::GetFont(const std::string& name)
{
	std::cout << "Game::GetFont()" << std::endl;
	auto iter = m_Fonts.find(name);
	if (iter != m_Fonts.end())
	{
		return iter->second;
	}

	return nullptr;
}
