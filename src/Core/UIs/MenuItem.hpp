#pragma once

#include <string>
#include "../Game.hpp"

class MenuItem
{
public:
  MenuItem(std::string text, void (*func)(Game*))
    :m_Text(text)
    ,m_Func(func)
  {

  }

  std::string GetText() { return m_Text; }
  void OnEnter(Game* game) { m_Func(game); }

private:
  std::string m_Text;
  void (*m_Func)(Game*);
};
