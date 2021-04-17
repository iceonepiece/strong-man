#pragma once

#include <vector>
#include "../../Core/Fixture.hpp"
#include "../../Core/Scene.hpp"
#include "../../Core/Game.hpp"
#include "../../Core/Entity.hpp"
#include "../../Core/Components.hpp"
#include "../../Core/TileEntity.hpp"
#include "../../Core/PlayerEntity.hpp"
#include "../../Core/EnemyEntity.hpp"

class XScene : public Scene
{
public:
	XScene(Game* game)
		:Scene(game)
		,m_Player(nullptr)
	{
		m_Player = new PlayerEntity(this);
		m_Tiles.emplace_back(new TileEntity(this, b2Vec2(12.0f, 20.0f), b2Vec2(40.0f, 2.0f)));
		m_Tiles.emplace_back(new TileEntity(this, b2Vec2(14.0f, 18.0f), b2Vec2(2.0f, 5.0f)));
		m_Tiles.emplace_back(new TileEntity(this, b2Vec2(20.0f, 16.0f), b2Vec2(2.0f, 8.0f)));

		auto &boxComp = m_Registry.get<BoxComponent>(m_Player->GetId());
		m_Camera.SetTargetBody(boxComp.Body);

		m_Enemies.emplace_back(new EnemyEntity(this));

		//m_Player = new PlayerEntity(this);
	}

	~XScene()
	{
		delete m_Player;

		for (auto tile : m_Tiles)
		{
			delete tile;
		}
		m_Tiles.clear();

		for (auto enemy : m_Enemies)
		{
			delete enemy;
		}
		m_Enemies.clear();
	}

private:
	PlayerEntity* m_Player;
	std::vector<TileEntity*> m_Tiles;
	std::vector<EnemyEntity*> m_Enemies;
};
