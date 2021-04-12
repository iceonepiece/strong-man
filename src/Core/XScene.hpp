#pragma once

#include <vector>
#include "Fixture.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "Entities.hpp"

class XScene : public Scene
{
public:
	XScene(Game* game): Scene(game)
	{
		PlayerEntity player(CreateEntity());
		TileEntity tile_1(CreateEntity());
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
