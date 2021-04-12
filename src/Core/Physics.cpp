#include "Physics.hpp"
#include <iostream>

Physics::Physics()
:m_World(b2Vec2(0.0f, 30.0f))
,m_VelocityIterations(6)
,m_PositionIterations(2)
{}

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

	for (auto fixture : fixtures)
	{
		b2PolygonShape shape;
		shape.SetAsBox(
			fixture.m_Width / 2,
			fixture.m_Height / 2,
			b2Vec2(fixture.m_XOffset, fixture.m_YOffet),
			0
		);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.isSensor = fixture.m_IsSensor;

		if (fixtureDef.isSensor)
		{
			fixtureDef.density = 0.0f;
		}

		body->SetFixedRotation(true);
		body->CreateFixture(&fixtureDef);
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
		b2PolygonShape shape;
		shape.SetAsBox(
			fixture.m_Width / 2,
			fixture.m_Height / 2,
			b2Vec2(fixture.m_XOffset, fixture.m_YOffet),
			0
		);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.isSensor = fixture.m_IsSensor;

		body->SetFixedRotation(true);
		body->CreateFixture(&fixtureDef);
	}

	return body;
}
