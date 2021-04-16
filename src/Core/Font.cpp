#include "Font.hpp"

TTF_Font *gFont = NULL;

Font::Font(std::string text, float x, float y)
  :UI(x, y)
  ,m_Text(text)
  ,m_Texture(nullptr)
{

}

void Font::Draw(Renderer* renderer)
{
  SDL_Color sdlColor;
  sdlColor.r = static_cast<Uint8>(255);
  sdlColor.g = static_cast<Uint8>(255);
  sdlColor.b = static_cast<Uint8>(255);
  sdlColor.a = 255;

  SDL_Surface* textSurface = TTF_RenderText_Solid(renderer->GetTTFFont(), m_Text.c_str(), sdlColor);
  if( textSurface == NULL )
  {
    SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }
  else
  {
    m_Texture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), textSurface);

    if( m_Texture == NULL )
    {
      SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    SDL_Rect renderQuad = { static_cast<int>(m_X), static_cast<int>(m_Y), 340, 36 };
    SDL_RenderCopy(renderer->GetSDLRenderer(), m_Texture, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
  }

}
