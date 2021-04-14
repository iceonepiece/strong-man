#pragma once

#include <box2d/box2d.h>
#include <iostream>

class Camera
{
public:
  Camera(float x, float y, float screenWidth, float screenHeight)
    :m_X(0.0f)
    ,m_Y(0.0f)
    ,m_ScreenWidth(screenWidth)
    ,m_ScreenHeight(screenHeight)
    ,m_PixelPerMetre(32)
    ,m_TargetBody(nullptr)
  {}

  void Update()
  {
    if (m_TargetBody)
    {
      b2Vec2 position = m_TargetBody->GetPosition();
      m_X = position.x * m_PixelPerMetre - (m_ScreenWidth / 2);
      m_Y = position.y * m_PixelPerMetre - (m_ScreenHeight / 2);
    }
  }

  void SetTargetBody(b2Body* body)
  {
    m_TargetBody = body;
  }

  float GetX() { return m_X; }
  float GetY() { return m_Y; }
  unsigned int GetPixelPerMetre() { return m_PixelPerMetre; }

private:
  float m_X;
  float m_Y;
  float m_ScreenWidth;
  float m_ScreenHeight;
  unsigned int m_PixelPerMetre;
  b2Body* m_TargetBody;
};
