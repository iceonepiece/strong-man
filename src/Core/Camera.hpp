#pragma once

#include <box2d/box2d.h>
#include "Math.hpp"
#include <iostream>

class Camera
{
public:
  Camera(vec2 position, vec2 screenSize)
    :m_Position(position)
    ,m_ScreenSize(screenSize)
    ,m_PixelPerMetre(32)
    ,m_TargetBody(nullptr)
  {}

  void Update()
  {
    if (m_TargetBody)
    {
      b2Vec2 position = m_TargetBody->GetPosition();
      m_Position.x = position.x * m_PixelPerMetre - (m_ScreenSize.x / 2);
      m_Position.y = position.y * m_PixelPerMetre - (m_ScreenSize.y / 2);
    }
  }

  void SetTargetBody(b2Body* body)
  {
    m_TargetBody = body;
  }

  const vec2& GetPosition() { return m_Position; }
  unsigned int GetPixelPerMetre() { return m_PixelPerMetre; }

private:
  vec2 m_Position;
  vec2 m_ScreenSize;
  unsigned int m_PixelPerMetre;
  b2Body* m_TargetBody;
};
