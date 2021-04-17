#include "../Core/Font.hpp"
#include "MyGame.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/XScene.hpp"

void MyGame::LoadData()
{
	Font* font = new Font();
	font->Load("src/Assets/DroidSans.ttf");

	Font* boldFont = new Font();
	boldFont->Load("src/Assets/DroidSans-Bold.ttf");

	m_Fonts.emplace("DROIDSANS", font);
	m_Fonts.emplace("DROIDSANS_BOLD", boldFont);

	Scene* menuScene = new MainMenuScene(this);
	Scene* xScene = new XScene(this);

	m_Scenes.emplace("MENU", menuScene);
	m_Scenes.emplace("LEVEL_1", xScene);

	m_CurrentScene = menuScene;
}

void MyGame::UnloadData()
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
