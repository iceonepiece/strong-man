#pragma once

#include <string>
#include <unordered_map>
#include <SDL2/SDL_ttf.h>
#include <box2d/box2d.h>

class Font
{
public:
  Font();
  ~Font();

  bool Load(const std::string& fileName);
	void Unload();

  void RenderText(SDL_Renderer* renderer, const std::string& text, const b2Vec2& position, const b2Vec3& color, unsigned int size);

private:
  std::unordered_map<int, TTF_Font*> m_FontData;
};
