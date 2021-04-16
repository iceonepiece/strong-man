#pragma once

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Input.hpp"

class Game
{
public:
	Game();

	bool Initialize();
	void Run();
	void Shutdown();

	void SetCurrentScene(std::string sceneName);
	unsigned int GetScreenWidth() { return m_ScreenWidth; }
	unsigned int GetScreenHeight() { return m_ScreenHeight; }

	class Font* GetFont(const std::string& name);

private:
	void ProcessInput();
	void Update();
	void Render();

	void LoadData();
	void UnloadData();

	bool m_Running;
	Uint32 m_TicksCount;
	unsigned int m_ScreenWidth;
	unsigned int m_ScreenHeight;

	class Renderer* m_Renderer;

	Input m_Input;

	class Scene* m_CurrentScene;
	std::unordered_map<std::string, class Scene*> m_Scenes;

	std::unordered_map<std::string, class Font*> m_Fonts;
};
