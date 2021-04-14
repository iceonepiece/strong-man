#include "Physics.hpp"
#include <iostream>

Physics::Physics()
:m_World(b2Vec2(0.0f, 25.0f))
,m_VelocityIterations(6)
,m_PositionIterations(2)
{
	m_World.SetContactListener(&m_ContactListener);
}

void Physics::Update(float deltaTime)
{
	m_World.Step(deltaTime, m_VelocityIterations, m_PositionIterations);
}

b2Body* Physics::CreateDynamicBody(float x, float y, std::vector<Fixture> fixtures)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	b2Body* body = m_World.CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	for (auto fixture : fixtures)
	{
		CreateFixture(body, fixture);
	}

	return body;
}

b2Body* Physics::CreateStaticBody(float x, float y, std::vector<Fixture> fixtures)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x, y);
	b2Body* body = m_World.CreateBody(&bodyDef);

	for (auto fixture : fixtures)
	{
		CreateFixture(body, fixture);
	}

	return body;
}

void Physics::CreateFixture(b2Body* body, Fixture& fixture)
{
	b2PolygonShape shape;
	shape.SetAsBox(
		fixture.m_Size.x / 2,
		fixture.m_Size.y / 2,
		fixture.m_Offset,
		0
	);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.isSensor = fixture.m_IsSensor;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(fixture.m_FixtureData);

	if (fixture.m_IsSensor)
	{
		fixtureDef.density = 0.0f;
	}

	body->CreateFixture(&fixtureDef);
}
