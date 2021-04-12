#pragma once

#include <vector>
#include "Fixture.hpp"
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

		Fixture fixture_1 { 2.0f, 4.0f, 0.0f, 0.0f, false };
		std::vector<Fixture> fixtures { fixture_1 };
		player.AddComponent<BoxComponent>(m_Physics.CreateDynamicBody(1.0f, 10.0f, fixtures));
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
		Fixture tileFixture_1 { 50.0f, 5.0f, 0.0f, 0.0f, false };
		std::vector<Fixture> tileFixtures { tileFixture_1 };
		tile_1.AddComponent<BoxComponent>(m_Physics.CreateStaticBody(26.0f, 30.0f, tileFixtures));
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
