#include "Scene.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "Systems.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "UI.hpp"
#include <iostream>

Scene::Scene(Game* game)
	:m_Game(game)
	,m_Camera(0.0f, 0.0f, m_Game->GetScreenWidth(), m_Game->GetScreenHeight())
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
	auto aiView = m_Registry.view<AIComponent>();

	for (auto [entity, aiComp]: aiView.each())
	{
		aiComp.m_BehaviorRoot->Tick();
	}

	auto view = m_Registry.view<MoveComponent, BoxComponent>();

	for (auto [entity, moveComp, boxComp]: view.each())
	{
		MoveSystem(moveComp, boxComp, deltaTime);
	}

	m_Physics.Update(deltaTime);

	m_Camera.Update();
}

void Scene::Render(Renderer* renderer)
{
	auto view = m_Registry.view<const BoxComponent>();

	for (auto [entity, box]: view.each())
	{
		renderer->DrawBody(box.Body, m_Camera);
	}

	for (auto ui : m_UIs)
	{
		ui->Draw(renderer);
	}
}
