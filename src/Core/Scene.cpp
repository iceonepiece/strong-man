#include "Scene.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "UI.hpp"
#include "Fixture.hpp"
#include "Behavior.hpp"

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

	for (auto heap : m_Heaps)
	{
		delete heap;
	}
	m_Heaps.clear();
}

void Scene::AddHeap(Heap* heap)
{
	m_Heaps.emplace_back(heap);
}
