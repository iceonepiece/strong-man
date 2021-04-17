#pragma once

#include "../Renderer.hpp"
#include "../UI.hpp"

class Text : public UI
{
public:
  Text(Scene* scene, std::string value, Font* font, unsigned int size = 18)
    :UI(scene, vec2(0.0f, 0.0f))
    ,m_Value(value)
    ,m_Size(size)
    ,m_Font(font)
  {}

  void ProcessInput(class Input& input)
  {

  }

  void Draw(class Renderer* renderer)
  {
    m_Font->RenderText(
      renderer->GetSDLRenderer(),
      m_Value,
      m_Position,
      vec3(255, 255, 255),
      m_Size
    );
  }

private:
  std::string m_Value;
  unsigned int m_Size;
  Font* m_Font;
};
