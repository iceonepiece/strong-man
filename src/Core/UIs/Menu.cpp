#include <box2d/box2d.h>
#include <iostream>
#include "Menu.hpp"
#include "../Font.hpp"
#include "../Renderer.hpp"
#include "../Scene.hpp"

const b2Vec3 COLOR_ITEM_NORMAL = b2Vec3(247, 237, 226);
const b2Vec3 COLOR_ITEM_SELECTED = b2Vec3(246, 189, 96);

Menu::Menu(Scene* scene, float x, float y, std::vector<std::string> items, Font* font)
  :UI(scene, x, y)
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

// position
// color
// size

void Menu::Draw(Renderer* renderer)
{
  SDL_Renderer* sdlRenderer = renderer->GetSDLRenderer();
  int space = m_FontSize + 8;

  for (int i = 0; i < m_Items.size(); i++)
  {
    if (i == m_CurrentItem)
    {
      m_Font->RenderText(sdlRenderer, m_Items[i], b2Vec2(m_X, m_Y + (i * space)), COLOR_ITEM_SELECTED, m_FontSize);
    }
    else
    {
      m_Font->RenderText(sdlRenderer, m_Items[i], b2Vec2(m_X, m_Y + (i * space)), COLOR_ITEM_NORMAL, m_FontSize);
    }
  }
}
