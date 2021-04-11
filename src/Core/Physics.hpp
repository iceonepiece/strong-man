#pragma once

#include <box2d/box2d.h>

class Physics
{
public:
	Physics();
	void Update(float deltaTime);
	b2World& GetWorld() { return m_World; }
	b2Body* CreateDynamicBody(float x, float y, float width, float height);
	b2Body* CreateStaticBody(float x, float y, float width, float height);

private:
	b2World m_World;
	int32 m_VelocityIterations;
	int32 m_PositionIterations;
};
