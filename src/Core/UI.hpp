#pragma once

#include "Math.hpp"

class UI
{
public:
  UI(class Scene* scene, vec2 position)
    :m_Scene(scene)
    ,m_Position(position)
  {}
  virtual ~UI() {}

  virtual void ProcessInput(class Input& input) = 0;
  virtual void Draw(class Renderer* renderer) = 0;

  void SetPosition(vec2 position) { m_Position = position; }

protected:
  vec2 m_Position;
  class Scene* m_Scene;
};
