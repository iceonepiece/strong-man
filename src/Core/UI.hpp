#pragma once

class UI
{
public:
  UI(class Scene* scene, float x, float y)
    :m_Scene(scene)
    ,m_X(x)
    ,m_Y(y)
  {}
  virtual ~UI() {}

  virtual void ProcessInput(class Input& input) = 0;
  virtual void Draw(class Renderer* renderer) = 0;

  void SetPosition(float x, float y)
  {
    m_X = x;
    m_Y = y;
  }

protected:
  float m_X;
  float m_Y;

  class Scene* m_Scene;
};
