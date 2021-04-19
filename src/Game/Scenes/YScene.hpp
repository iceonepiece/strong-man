#pragma once

#include "../../Core/Game.hpp"
#include "../../Core/EntityFactory.hpp"
#include "LevelScene.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Tile.hpp"
#include "../Entities/Enemy.hpp"

class YScene : public LevelScene
{
public:
	YScene(Game* game): LevelScene(game)
	{
		EntityFactory factory = EntityFactory(this);

		auto player = factory.Create<Player>();

		factory.Create<Tile>(12.0f, 20.0f, 40.0f, 2.0f);
		factory.Create<Tile>(14.0f, 18.0f, 2.0f, 5.0f);
		factory.Create<Tile>(20.0f, 16.0f, 2.0f, 8.0f);

		factory.Create<Enemy>();

		auto &boxComp = m_Registry.get<BoxComponent>(player);
		m_Camera.SetTargetBody(boxComp.Body);
	}

	~YScene()
	{
	}
};
