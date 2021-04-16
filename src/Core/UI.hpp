#pragma once

#include "Renderer.hpp"

class UI
{
public:
  UI(float x, float y): m_X(x), m_Y(y) {}
  virtual ~UI() {}

  virtual void Draw(Renderer* renderer) {}

protected:
  float m_X;
  float m_Y;
};
