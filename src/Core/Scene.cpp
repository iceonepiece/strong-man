#include "Scene.hpp"
#include "Entity.hpp"
#include "Components.hpp"

Scene::Scene(class Game* game)
	:m_Game(game)
{

}

Scene::~Scene()
{

}

void Scene::Update(float deltaTime)
{
	m_Physics.Update(deltaTime);
}

void Scene::Render(SDL_Renderer* renderer)
{
	auto view = m_Registry.view<const BoxComponent>();

	for (auto [entity, box]: view.each())
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_Rect rect {
			static_cast<int>(box.Body->GetPosition().x),
			static_cast<int>(box.Body->GetPosition().y),
			static_cast<int>(box.Width),
			static_cast<int>(box.Height),
		};

		SDL_RenderFillRect(renderer, &rect);
	}
}

Entity Scene::CreateEntity()
{
	Entity entity = Entity(m_Registry.create(), this);
	return entity;
}
