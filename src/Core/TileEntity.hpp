#pragma once

#include <iostream>
#include "Entity.hpp"
#include "Fixture.hpp"

class TileEntity : public Entity
{
public:
	TileEntity(Scene* scene, b2Vec2 position, b2Vec2 size)
		:Entity(scene)
	{
		m_FixtureData = new FixtureData(this, "tile");
		Fixture tileFixture(b2Vec2(size.x, size.y), b2Vec2(0.0f, 0.0f));
		tileFixture.SetFixtureData(m_FixtureData);
		std::vector<Fixture> tileFixtures { tileFixture };
		AddComponent<BoxComponent>(m_Scene->GetPhysics().CreateStaticBody(position.x, position.y, tileFixtures));
	}

	~TileEntity()
	{
		std::cout << "TileEntity destructor" << std::endl;
		delete m_FixtureData;
	}

private:
	FixtureData* m_FixtureData;
};
