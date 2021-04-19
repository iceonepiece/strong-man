#include "../Core/Font.hpp"
#include "MyGame.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/YScene.hpp"

void MyGame::LoadData()
{
	Font* font = new Font();
	font->Load("src/Assets/DroidSans.ttf");

	Font* boldFont = new Font();
	boldFont->Load("src/Assets/DroidSans-Bold.ttf");

	m_Fonts.emplace("DROIDSANS", font);
	m_Fonts.emplace("DROIDSANS_BOLD", boldFont);

	//Scene* menuScene = new MainMenuScene(this);
	Scene* yScene = new YScene(this);

	//m_Scenes.emplace("MENU", menuScene);
	m_Scenes.emplace("LEVEL_1", yScene);

	m_CurrentScene = yScene;
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
