#pragma once

#include <string>
#include "Entity.hpp"
#include "Fixture.hpp"

class PlayerFixtureData : public FixtureData
{
public:
	PlayerFixtureData(Entity* entity): FixtureData(entity, "PLAYER")
	{
		std::cout << "PlayerFixtureData constructor: " << m_Tag << std::endl;
	}

	void BeginContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA);
	void EndContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA);
};

class PlayerEntity : public Entity
{
public:
	PlayerEntity(Scene* scene)
		:Entity(scene)
	{
		m_FixtureData = new PlayerFixtureData(this);
		Fixture bodyFixture(b2Vec2(1.0f, 2.0f), b2Vec2(0.0f, 0.0f));
		bodyFixture.SetFixtureData(m_FixtureData);

		Fixture footFixture(b2Vec2(0.5f, 1.0f), b2Vec2(0.0f, 0.0f), true);
		std::vector<Fixture> fixtures { bodyFixture };
		AddComponent<BoxComponent>(m_Scene->GetPhysics().CreateDynamicBody(1.0f, 10.0f, fixtures));
		AddComponent<MoveComponent>();

		InputListener moveLeft;
		moveLeft.m_KeyCode = SDL_SCANCODE_LEFT;
		moveLeft.m_ButtonState = EHeld;
		moveLeft.m_Command = "MOVE_LEFT";

		InputListener moveRight;
		moveRight.m_KeyCode = SDL_SCANCODE_RIGHT;
		moveRight.m_ButtonState = EHeld;
		moveRight.m_Command = "MOVE_RIGHT";

		InputListener moveJump;
		moveJump.m_KeyCode = SDL_SCANCODE_SPACE;
		moveJump.m_ButtonState = EPressed;
		moveJump.m_Command = "MOVE_JUMP";

		std::vector<InputListener> listeners { moveLeft, moveRight, moveJump };
		AddComponent<InputComponent>(listeners);
	}

	~PlayerEntity()
	{
		std::cout << "PlayerEntity destructor" << std::endl;
		delete m_FixtureData;
	}

	void AddGroundFixtures(FixtureData* fixtureData)
	{
		m_GroundFixtures.emplace_back(fixtureData);
	}

	bool RemoveGroundFixtures(FixtureData* fixtureData)
	{
		auto iter = std::find(m_GroundFixtures.begin(), m_GroundFixtures.end(), fixtureData);
		if (iter != m_GroundFixtures.end())
		{
			m_GroundFixtures.erase(iter);
			return true;
		}

		return false;
	}

private:
	FixtureData* m_FixtureData;
	std::vector<FixtureData*> m_GroundFixtures;
};


void PlayerFixtureData::BeginContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA)
{
	std::cout << "PlayerFixtureData BeginContact(): " << m_Tag << std::endl;

	b2WorldManifold worldManifold;
	contact->GetWorldManifold( &worldManifold );
	std::cout << "normal: " << worldManifold.normal.x << " : " << worldManifold.normal.y << std::endl;

	int yTarget = 1;
	if (!isA) {
		yTarget = -1;
	}

	if (worldManifold.normal.x == 0 && worldManifold.normal.y == yTarget)
	{
		((PlayerEntity*)m_Entity)->AddGroundFixtures(otherFixtureData);
		auto &moveComp = m_Entity->GetScene()->GetRegistry().get<MoveComponent>(m_Entity->GetId());
		moveComp.m_NumGrounds++;

		std::cout << "moveComp.m_NumGrounds: " << moveComp.m_NumGrounds << " target: " << yTarget << std::endl;
	}
}

void PlayerFixtureData::EndContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA)
{
	bool success = ((PlayerEntity*)m_Entity)->RemoveGroundFixtures(otherFixtureData);

	if (success)
	{
		auto &moveComp = m_Entity->GetScene()->GetRegistry().get<MoveComponent>(m_Entity->GetId());
		moveComp.m_NumGrounds--;
		std::cout << "moveComp.m_NumGrounds: " << moveComp.m_NumGrounds << std::endl;
	}
}
