#include "Scene.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "Systems.hpp"
#include "Renderer.hpp"
#include <iostream>

Scene::Scene(class Game* game)
	:m_Game(game)
{

}

Scene::~Scene()
{

}

void Scene::ProcessInput(Input& input)
{
	auto view = m_Registry.view<InputComponent, MoveComponent>();

	for (auto [entity, inputComp, moveComp]: view.each())
	{
		moveComp.m_MoveState = MS_IDLE;
		moveComp.m_Jump = false;

		for (auto listener : inputComp.m_Listeners)
		{
			ButtonState buttonState = input.GetKeyboardState().GetKeyState(listener.m_KeyCode);
			if (buttonState == listener.m_ButtonState)
			{
				if (listener.m_Command == "MOVE_LEFT")
				{
					moveComp.m_MoveState = MS_LEFT;
				}
				else if (listener.m_Command == "MOVE_RIGHT")
				{
					moveComp.m_MoveState = MS_RIGHT;
				}
				else if (listener.m_Command == "MOVE_JUMP")
				{
					moveComp.m_Jump = true;
				}
			}
		}
	}
}

void Scene::Update(float deltaTime)
{
	// check movements
	auto view = m_Registry.view<MoveComponent, BoxComponent>();

	for (auto [entity, moveComp, boxComp]: view.each())
	{
		MoveSystem(moveComp, boxComp, deltaTime);
	}

	m_Physics.Update(deltaTime);
}

void Scene::Render(Renderer* renderer)
{
	auto view = m_Registry.view<const BoxComponent>();

	for (auto [entity, box]: view.each())
	{
		renderer->DrawBody(box.Body);
	}
}
