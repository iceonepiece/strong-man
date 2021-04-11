#include "Scene.hpp"
#include "Entity.hpp"
#include "Components.hpp"
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
		b2Body* body = boxComp.Body;
		if (body)
		{
			b2Vec2 velocity = body->GetLinearVelocity();
			float desiredVelocity = 0;

			switch (moveComp.m_MoveState)
			{
				case MS_LEFT:  desiredVelocity = -80; break;
				case MS_IDLE:  desiredVelocity =  0; break;
				case MS_RIGHT: desiredVelocity =  80; break;
			}

			float velocityChange = desiredVelocity - velocity.x;
			float force = body->GetMass() * velocityChange / deltaTime;

			body->SetLinearVelocity(b2Vec2(desiredVelocity, velocity.y));
		}
	}

	m_Physics.Update(deltaTime);
}

void Scene::Render(Renderer* renderer)
{
	auto view = m_Registry.view<const BoxComponent>();

	for (auto [entity, box]: view.each())
	{
		renderer->DrawRect(
			static_cast<int>(box.Body->GetPosition().x - (box.Width / 2)),
			static_cast<int>(box.Body->GetPosition().y - (box.Height / 2)),
			static_cast<int>(box.Width),
			static_cast<int>(box.Height)
		);
	}
}

Entity Scene::CreateEntity()
{
	Entity entity = Entity(m_Registry.create(), this);
	return entity;
}
