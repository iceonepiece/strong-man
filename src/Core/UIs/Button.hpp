#pragma once

#include "../Scene.hpp"
#include "Text.hpp"

class Button : public UI
{
public:
  Button(Scene* scene)
    :UI(scene, 0.0f, 0.0f)
  {
  }

  ~Button()
  {
    if (m_Text)
    {
      delete m_Text;
    }
  }

  void ProcessInput(class Input& input)
  {

  }

  void Draw(class Renderer* renderer)
  {
    m_Text->Draw(renderer);
  }

  void SetText(Text* text)
  {
    m_Text = text;
  }

private:
  Text* m_Text;
};
