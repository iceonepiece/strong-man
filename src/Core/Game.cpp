#include "Game.hpp"
#include "Renderer.hpp"
#include "Font.hpp"
#include "../Game/Scenes/XScene.hpp"
#include "../Game/Scenes/YScene.hpp"
#include "../Game/Scenes/MenuScene.hpp"

Game::Game()
	:m_Running(true)
	,m_Renderer(nullptr)
	,m_CurrentScene(nullptr)
	,m_ScreenWidth(1280)
	,m_ScreenHeight(720)
{}

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
	m_Renderer->Shutdown();
	delete m_Renderer;
	SDL_Quit();
}

void Game::SetCurrentScene(std::string sceneName)
{
	auto iter = m_Scenes.find(sceneName);
	if (iter != m_Scenes.end())
	{
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

void Game::LoadData()
{
	Font* font = new Font();
	font->Load("src/Assets/DroidSans.ttf");

	Font* boldFont = new Font();
	boldFont->Load("src/Assets/DroidSans-Bold.ttf");

	m_Fonts.emplace("DROIDSANS", font);
	m_Fonts.emplace("DROIDSANS_BOLD", boldFont);

	Scene* menuScene = new MenuScene(this);
	Scene* xScene = new XScene(this);
	Scene* yScene = new YScene(this);

	m_Scenes.emplace("MENU", menuScene);
	m_Scenes.emplace("X", xScene);
	m_Scenes.emplace("Y", yScene);

	m_CurrentScene = xScene;
}

void Game::UnloadData()
{
	for (auto font : m_Fonts)
	{
		font.second->Unload();
		delete font.second;
	}

	for (auto scene : m_Scenes)
	{
		delete scene.second;
	}
	m_Scenes.clear();
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
