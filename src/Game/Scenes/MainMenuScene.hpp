#pragma once

#include "../../Core/Math.hpp"
#include "../../Core/Game.hpp"
#include "UIScene.hpp"
#include "../../Core/UI.hpp"
#include "../../Core/UIs/Text.hpp"
#include "../../Core/UIs/Menu.hpp"
#include "../../Core/UIs/MenuItem.hpp"

class MainMenuScene : public UIScene
{
public:
  MainMenuScene(Game* game)
    :UIScene(game)
  {
    Font* font = m_Game->GetFont("DROIDSANS");
    Font* boldFont = m_Game->GetFont("DROIDSANS_BOLD");

    Text* directedByText = new Text(this, "DIRECTED BY", font, 24);
    directedByText->SetPosition(vec2(40, 20));

    Text* directorText = new Text(this, "KIM MI YOUNG", boldFont, 36);
    directorText->SetPosition(vec2(40, 60));

    m_UIs.emplace_back(directedByText);
    m_UIs.emplace_back(directorText);

    Menu* menu = new Menu(this, 60.0f, 112.0f, font);
    MenuItem* startMenuItem = new MenuItem(
      "Start",
      [](class Game* game)
      {
        std::cout << "start onEnter()" << std::endl;
        game->SetCurrentScene("LEVEL_1");
      }
    );

    MenuItem* optionsMenuItem = new MenuItem(
      "Options",
      [](class Game* game)
      {
        std::cout << "options onEnter()" << std::endl;
      }
    );

    MenuItem* exitMenuItem = new MenuItem(
      "Exit",
      [](class Game* game)
      {
        std::cout << "exit onEnter()" << std::endl;
      }
    );

    menu->AddItem(startMenuItem);
    menu->AddItem(optionsMenuItem);
    menu->AddItem(exitMenuItem);
    m_UIs.emplace_back(menu);
  }
};
