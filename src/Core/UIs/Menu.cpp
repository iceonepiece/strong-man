#include <box2d/box2d.h>
#include <iostream>
#include "Menu.hpp"
#include "../Math.hpp"
#include "../Font.hpp"
#include "../Renderer.hpp"
#include "../Scene.hpp"

const vec3 COLOR_ITEM_NORMAL = vec3(247, 237, 226);
const vec3 COLOR_ITEM_SELECTED = vec3(246, 189, 96);

Menu::Menu(Scene* scene, float x, float y, std::vector<std::string> items, Font* font)
  :UI(scene, vec2(x, y))
  ,m_Items(items)
  ,m_Font(font)
  ,m_FontSize(36)
{

}

Menu::~Menu()
{

}

void Menu::ProcessInput(Input& input)
{
  if (m_Items.size() > 0)
  {
    const KeyboardState state = input.GetKeyboardState();

    if (state.GetKeyState(SDL_SCANCODE_RETURN) == EPressed)
    {
      std::cout << "ENTER: " << m_Items[m_CurrentItem] << std::endl;
      //m_Items[m_CurrentItem].OnEnter();
    }
    else if (state.GetKeyState(SDL_SCANCODE_UP) == EPressed)
    {
      if (m_CurrentItem > 0)
      {
        m_CurrentItem--;
      }
    }
    else if (state.GetKeyState(SDL_SCANCODE_DOWN) == EPressed)
    {
      if (m_CurrentItem < m_Items.size() - 1)
      {
        m_CurrentItem++;
      }
    }
  }
}

void Menu::Draw(Renderer* renderer)
{
  SDL_Renderer* sdlRenderer = renderer->GetSDLRenderer();
  int space = m_FontSize + 8;


  for (int i = 0; i < m_Items.size(); i++)
  {
    vec3 color = COLOR_ITEM_NORMAL;
    if (i == m_CurrentItem)
    {
      color = COLOR_ITEM_SELECTED;
    }

    m_Font->RenderText(sdlRenderer, m_Items[i], vec2(m_Position.x, m_Position.y + (i * space)), color, m_FontSize);
  }
}
