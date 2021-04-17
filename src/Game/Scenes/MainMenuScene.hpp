#pragma once

#include "../../Core/Math.hpp"
#include "../../Core/Game.hpp"
#include "UIScene.hpp"
#include "../../Core/UI.hpp"
#include "../../Core/UIs/Text.hpp"
#include "../../Core/UIs/Menu.hpp"

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

    std::vector<std::string> menuItems { "Start", "Option", "Exit" };
    m_UIs.emplace_back(new Menu(this, 60.0f, 112.0f, menuItems, font));
  }
};
