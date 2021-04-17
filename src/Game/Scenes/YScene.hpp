#pragma once

#include "../../Core/Scene.hpp"
#include "../../Core/Game.hpp"

class YScene : public Scene
{
public:
	YScene(Game* game): Scene(game), m_Player(nullptr)
	{
		//m_Player = new PlayerEntity(this);
		//auto &boxComp = m_Registry.get<BoxComponent>(m_Player->GetId());
		//m_Camera.SetTargetBody(boxComp.Body);
	}

	~YScene()
	{
		//delete m_Player;
	}

private:
	PlayerEntity* m_Player;
};
