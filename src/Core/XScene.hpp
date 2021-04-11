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
		b2Body* playerBody = m_Physics.CreateDynamicBody(50.0f, 10.0f, 100.0f, 100.0f);
		player.AddComponent<BoxComponent>(100.0f, 100.0f, playerBody);
		player.AddComponent<MoveComponent>();

		InputListener moveLeft;
		moveLeft.m_KeyCode = SDL_SCANCODE_LEFT;
		moveLeft.m_ButtonState = EHeld;
		moveLeft.m_Command = "MOVE_LEFT";

		InputListener moveRight;
		moveRight.m_KeyCode = SDL_SCANCODE_RIGHT;
		moveRight.m_ButtonState = EHeld;
		moveRight.m_Command = "MOVE_RIGHT";

		std::vector<InputListener> listeners { moveLeft, moveRight };
		player.AddComponent<InputComponent>(listeners);

		struct InputListener
		{
			SDL_Scancode m_KeyCode;
			ButtonState m_ButtonState;
			std::string m_Command;
		};

		Entity tile_1 = CreateEntity();
		b2Body* tileBody_1 = m_Physics.CreateStaticBody(50.0f, 400.0f, 500.0f, 50.0f);
		tile_1.AddComponent<BoxComponent>(500.0f, 50.0f, tileBody_1);
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
