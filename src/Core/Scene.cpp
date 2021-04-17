#include "Scene.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "UI.hpp"
#include <iostream>

Scene::Scene(Game* game)
	:m_Game(game)
	,m_Camera(
		vec2(0.0f, 0.0f),
		vec2((float)m_Game->GetScreenWidth(), (float)m_Game->GetScreenHeight())
	)
{

}

Scene::~Scene()
{
	for (auto ui : m_UIs)
	{
		delete ui;
	}
	m_UIs.clear();
}
