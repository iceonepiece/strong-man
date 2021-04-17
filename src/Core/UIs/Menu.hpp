#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "../UI.hpp"
#include "../Input.hpp"

class Menu : public UI
{
public:
  Menu(class Scene* scene, float x, float y, class Font* font);
  ~Menu();

  void ProcessInput(Input& input);
  void Draw(class Renderer* renderer);

  void AddItem(class MenuItem*);

private:
  class Font* m_Font;
  int m_FontSize;
  std::vector<class MenuItem*> m_Items;
  int m_CurrentItem;
};
