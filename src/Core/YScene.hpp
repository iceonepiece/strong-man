#pragma once

#include "Scene.hpp"
#include "Game.hpp"

class YScene : public Scene
{
public:
  YScene(Game* game): Scene(game) {}
  ~YScene() {}

  void ProcessInput(const uint8_t* keyState)
  {
    if (keyState[SDL_SCANCODE_SPACE])
    {
      m_Game->SetCurrentScene("X");
    }
  }

  void Update(float deltaTime)
  {

  }

  void Render(SDL_Renderer* renderer)
  {
    SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
    SDL_Rect rect { 200, 200, 200, 200 };
    SDL_RenderFillRect(renderer, &rect);
  }
};
