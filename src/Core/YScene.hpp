#pragma once

#include "Scene.hpp"
#include "Game.hpp"

class YScene : public Scene
{
public:
  YScene(Game* game): Scene(game) {}
  ~YScene() {}

  void ProcessInput(Input& input)
  {
    if (input.GetKeyboardState().GetKeyState(SDL_SCANCODE_SPACE) == EPressed)
    {
      m_Game->SetCurrentScene("X");
    }
  }
};
