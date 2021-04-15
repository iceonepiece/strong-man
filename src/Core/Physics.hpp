#pragma once

#include <vector>
#include <iostream>
#include <box2d/box2d.h>
#include "Fixture.hpp"

class ContactListener : public b2ContactListener
{
  void BeginContact(b2Contact* contact)
  {
		std::cout << "Begin " << std::endl;
    b2FixtureUserData fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    b2FixtureUserData fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    FixtureData* fixtureDataA = (FixtureData*)fixtureUserDataA.pointer;
    FixtureData* fixtureDataB = (FixtureData*)fixtureUserDataB.pointer;

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    if (fixtureDataA && fixtureDataB)
    {
      fixtureDataA->BeginContact(fixtureDataB, contact, true);
      fixtureDataB->BeginContact(fixtureDataA, contact, false);
    }
	}

	void EndContact(b2Contact* contact)
  {
		std::cout << "End " << std::endl;

    b2FixtureUserData fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    b2FixtureUserData fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    FixtureData* fixtureDataA = (FixtureData*)fixtureUserDataA.pointer;
    FixtureData* fixtureDataB = (FixtureData*)fixtureUserDataB.pointer;

    if (fixtureDataA && fixtureDataB)
    {
      fixtureDataA->EndContact(fixtureDataB, contact, true);
      fixtureDataB->EndContact(fixtureDataA, contact, false);
    }
	}
};

class Physics
{
public:
	Physics();
	void Update(float deltaTime);
	b2World& GetWorld() { return m_World; }
	b2Body* CreateDynamicBody(float x, float y, std::vector<Fixture> fixtures);
	b2Body* CreateStaticBody(float x, float y, std::vector<Fixture> fixtures);

private:
  void CreateFixture(b2Body* body, Fixture& fixture);

	b2World m_World;
	ContactListener m_ContactListener;
	int32 m_VelocityIterations;
	int32 m_PositionIterations;
};
