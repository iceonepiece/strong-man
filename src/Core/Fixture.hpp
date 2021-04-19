#pragma once

#include <string>
#include <iostream>
#include <box2d/box2d.h>
#include "../External/entt/entt.hpp"
#include "Heap.hpp"

class FixtureData : public Heap
{
public:
	FixtureData(class Scene* scene, entt::entity entity, std::string tag = "");
	virtual ~FixtureData();

	virtual void BeginContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA);
	virtual void EndContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA);

	std::string m_Tag;
	entt::entity m_Entity;
};

class Fixture
{
public:
	Fixture(b2Vec2 size, b2Vec2 offset, bool isSensor = false)
		:m_Size(size)
		,m_Offset(offset)
		,m_IsSensor(isSensor)
		,m_FixtureData(nullptr)
	{
	}

	void SetFixtureData(FixtureData* fixtureData)
	{
		m_FixtureData = fixtureData;
	}

	b2Vec2 m_Size;
	b2Vec2 m_Offset;
	bool m_IsSensor;
	FixtureData* m_FixtureData;
};
