#pragma once

#include <string>
#include <iostream>
#include <box2d/box2d.h>

class FixtureData
{
public:
	FixtureData(class Entity* entity, std::string tag = "")
		:m_Entity(entity)
		,m_Tag(tag)
	{
		std::cout << "FixtureData constructor: " << m_Tag << std::endl;
	}

	virtual ~FixtureData()
	{
		std::cout << "FixtureData destructor: " << m_Tag << std::endl;
	}

	virtual void BeginContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA) {};
	virtual void EndContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA) {};

	std::string m_Tag;
	class Entity* m_Entity;
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
