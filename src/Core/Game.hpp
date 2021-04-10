#pragma once

#include <unordered_map>
#include <string>
#include "SDL2/SDL.h"
#include "Input.hpp"

class Game
{
public:
	Game();

	bool Initialize();
	void Run();
	void Shutdown();

	void SetCurrentScene(std::string sceneName);

private:
	void ProcessInput();
	void Update();
	void Render();

	void LoadData();
	void UnloadData();

	bool m_Running;
	Uint32 m_TicksCount;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Input m_Input;

	class Scene* m_CurrentScene;
	std::unordered_map<std::string, class Scene*> m_Scenes;
};
