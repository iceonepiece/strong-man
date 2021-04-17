#include "../../Core/Renderer.hpp"
#include "../Components/Components.hpp"
#include "../Systems/Systems.hpp"
#include "LevelScene.hpp"

LevelScene::LevelScene(Game* game)
	:Scene(game)
{

}

LevelScene::~LevelScene()
{

}

void LevelScene::ProcessInput(Input& input)
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

void LevelScene::Update(float deltaTime)
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

void LevelScene::Render(Renderer* renderer)
{
	auto view = m_Registry.view<const BoxComponent>();

	for (auto [entity, box]: view.each())
	{
		renderer->DrawBody(box.Body, m_Camera);
	}
}
