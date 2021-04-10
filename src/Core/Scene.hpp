#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "Input.hpp"

class Scene
{
public:
  Scene(class Game* game);
  virtual ~Scene();

  virtual void ProcessInput(Input& input) = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void Render(SDL_Renderer* renderer) = 0;

protected:
  class Game* m_Game;

  std::vector<class Entity*> m_Entities;
};
