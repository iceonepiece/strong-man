#pragma once

#include "Scene.hpp"
#include "Game.hpp"
#include "Entity.hpp"
#include "Components.hpp"

class XScene : public Scene
{
public:
	XScene(Game* game): Scene(game)
	{
		Entity player = CreateEntity();
		b2Body* playerBody = m_Physics.CreateDynamicBody(10.0f, 10.0f, 2.0f, 4.0f);
		player.AddComponent<BoxComponent>(2.0f, 4.0f, playerBody);
		player.AddComponent<MoveComponent>();

		InputListener moveLeft;
		moveLeft.m_KeyCode = SDL_SCANCODE_LEFT;
		moveLeft.m_ButtonState = EHeld;
		moveLeft.m_Command = "MOVE_LEFT";

		InputListener moveRight;
		moveRight.m_KeyCode = SDL_SCANCODE_RIGHT;
		moveRight.m_ButtonState = EHeld;
		moveRight.m_Command = "MOVE_RIGHT";

		InputListener moveJump;
		moveJump.m_KeyCode = SDL_SCANCODE_SPACE;
		moveJump.m_ButtonState = EPressed;
		moveJump.m_Command = "MOVE_JUMP";

		std::vector<InputListener> listeners { moveLeft, moveRight, moveJump };
		player.AddComponent<InputComponent>(listeners);

		struct InputListener
		{
			SDL_Scancode m_KeyCode;
			ButtonState m_ButtonState;
			std::string m_Command;
		};

		Entity tile_1 = CreateEntity();
		b2Body* tileBody_1 = m_Physics.CreateStaticBody(10.0f, 30.0f, 50.0f, 5.0f);
		tile_1.AddComponent<BoxComponent>(50.0f, 5.0f, tileBody_1);
		tile_1.AddComponent<MoveComponent>();
	}

	~XScene() {}

	void ProcessInput(Input& input)
	{
		if (input.GetKeyboardState().GetKeyState(SDL_SCANCODE_SPACE) == EPressed)
		{
			m_Game->SetCurrentScene("Y");
		}
	}
};
