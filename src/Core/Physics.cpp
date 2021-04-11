#include "Physics.hpp"

Physics::Physics()
:m_World(b2Vec2(0.0f, 28.0f))
,m_VelocityIterations(6)
,m_PositionIterations(2)
{}

void Physics::Update(float deltaTime)
{
  m_World.Step(deltaTime, m_VelocityIterations, m_PositionIterations);
}

b2Body* Physics::CreateBody(float x, float y, float width, float height)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(x, y);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(width / 2, height / 2);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.0f;

  b2Body* body = m_World.CreateBody(&bodyDef);
  body->SetFixedRotation(true);
  body->CreateFixture(&fixtureDef);

  return body;
}
