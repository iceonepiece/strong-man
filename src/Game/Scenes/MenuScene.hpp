#pragma once

#include "../../Core/Game.hpp"
#include "../../Core/Scene.hpp"
#include "../../Core/UI.hpp"
#include "../../Core/Font.hpp"

class MenuScene : public Scene
{
public:
  MenuScene(Game* game)
    :Scene(game)
  {
    m_UIs.emplace_back(new Font("DIRECTED BY", 120.0f, 16.0f));
    m_UIs.emplace_back(new Font("KIM MI YOUNG", 120.0f, 64.0f));
  }
};
