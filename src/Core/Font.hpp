#pragma once

#include <string>
#include <unordered_map>
#include <SDL2/SDL_ttf.h>
#include "Math.hpp"

class Font
{
public:
  Font();
  ~Font();

  bool Load(const std::string& fileName);
	void Unload();

  void RenderText(SDL_Renderer* renderer, const std::string& text, const vec2& position, const vec3& color, unsigned int size);

private:
  std::unordered_map<int, TTF_Font*> m_FontData;
};
