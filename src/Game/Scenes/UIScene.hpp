#pragma once

#include "../../Core/Scene.hpp"

class UIScene : public Scene
{
public:
  UIScene(class Game* game);
  virtual ~UIScene();

  void ProcessInput(Input& input);
  void Update(float deltaTime);
  void Render(class Renderer* renderer);
};
