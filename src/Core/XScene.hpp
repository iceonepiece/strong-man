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
    b2Body* playerBody = m_Physics.CreateBody(10.0f, 10.0f, 100.0f, 100.0f);
    player.AddComponent<BoxComponent>(100.0f, 100.0f, playerBody);
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
