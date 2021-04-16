#pragma once

#include <SDL2/SDL_ttf.h>
#include "UI.hpp"

class Font : public UI
{
public:
  Font(std::string text, float x, float y);
  void Draw(Renderer* renderer);

private:
  std::string m_Text;
  SDL_Texture* m_Texture;
};
