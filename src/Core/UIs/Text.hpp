#pragma once

#include "../Renderer.hpp"

class Text : public UI
{
public:
  Text(Scene* scene, std::string value, Font* font, unsigned int size = 18)
    :UI(scene, 0.0f, 0.0f)
    ,m_Value(value)
    ,m_Size(size)
    ,m_Font(font)
  {}

  void ProcessInput(class Input& input)
  {

  }

  void Draw(class Renderer* renderer)
  {
    std::cout << "Text: " << m_Value << " is drawn on the screen." << std::endl;
    m_Font->RenderText(
      renderer->GetSDLRenderer(),
      m_Value,
      b2Vec2(m_X, m_Y),
      b2Vec3(255, 255, 255),
      m_Size
    );
  }

private:
  std::string m_Value;
  unsigned int m_Size;
  Font* m_Font;
};
