#pragma once

#include <vector>
#include <SDL2/SDL.h>

class Scene
{
public:
  Scene(class Game* game);
  virtual ~Scene();

  virtual void ProcessInput(const uint8_t* keyState) = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void Render(SDL_Renderer* renderer) = 0;

protected:
  class Game* m_Game;

  std::vector<class Entity*> m_Entities;
};
