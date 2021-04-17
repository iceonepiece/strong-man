#pragma once

#include "../../Core/Scene.hpp"

class LevelScene : public Scene
{
public:
  LevelScene(class Game* game);
  virtual ~LevelScene();

  void ProcessInput(Input& input);
  void Update(float deltaTime);
  void Render(class Renderer* renderer);
};
