#pragma once

#include "Scene.hpp"
#include "Game.hpp"

class XScene : public Scene
{
public:
  XScene(Game* game): Scene(game) {}
  ~XScene() {}

  void ProcessInput(Input& input)
  {
    if (input.GetKeyboardState().GetKeyState(SDL_SCANCODE_SPACE) == EPressed)
    {
      m_Game->SetCurrentScene("Y");
    }
  }

  void Update(float deltaTime)
  {

  }

  void Render(SDL_Renderer* renderer)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect { 200, 200, 200, 200 };
    SDL_RenderFillRect(renderer, &rect);
  }
};
