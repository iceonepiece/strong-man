#pragma once

#include <vector>
#include "Fixture.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "TileEntity.hpp"
#include "PlayerEntity.hpp"

class XScene : public Scene
{
public:
	XScene(Game* game)
		:Scene(game)
		,m_Player(nullptr)
	{
		m_Player = new PlayerEntity(this);
		m_Tiles.emplace_back(new TileEntity(this, b2Vec2(12.0f, 20.0f), b2Vec2(20.0f, 2.0f)));
		m_Tiles.emplace_back(new TileEntity(this, b2Vec2(12.0f, 18.0f), b2Vec2(2.0f, 5.0f)));
		m_Tiles.emplace_back(new TileEntity(this, b2Vec2(18.0f, 16.0f), b2Vec2(2.0f, 8.0f)));
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
	}

private:
	PlayerEntity* m_Player;
	std::vector<TileEntity*> m_Tiles;
};
