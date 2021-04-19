#pragma once

#include "../Components/Components.hpp"

class PlayerFixtureData : public FixtureData
{
public:
	PlayerFixtureData(class Scene* scene, entt::entity entity): FixtureData(scene, entity, "PLAYER")
	{
		std::cout << "PlayerFixtureData constructor: " << m_Tag << std::endl;
	}

	void BeginContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA);
	void EndContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA);
};

class Player
{
public:
  static entt::entity Create(EntityFactory* factory)
  {
    auto entity = factory->Entity();

  	Fixture bodyFixture(b2Vec2(1.0f, 2.0f), b2Vec2(0.0f, 0.0f));
    FixtureData* fixtureData = new PlayerFixtureData(factory->GetScene(), entity);
  	bodyFixture.SetFixtureData(fixtureData);
  	std::vector<Fixture> fixtures { bodyFixture };
  	factory->AddComponent<BoxComponent>(entity, factory->GetScene()->GetPhysics().CreateDynamicBody(1.0f, 10.0f, fixtures));
  	factory->AddComponent<MoveComponent>(entity);

    InputListener moveLeft { SDL_SCANCODE_LEFT, EHeld, "MOVE_LEFT" };
    InputListener moveRight { SDL_SCANCODE_RIGHT, EHeld, "MOVE_RIGHT" };
    InputListener moveJump { SDL_SCANCODE_SPACE, EPressed, "MOVE_JUMP" };
    std::vector<InputListener> listeners { moveLeft, moveRight, moveJump };
    factory->AddComponent<InputComponent>(entity, listeners);

    return entity;
  }
};

void PlayerFixtureData::BeginContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA)
{
	b2WorldManifold worldManifold;
	contact->GetWorldManifold( &worldManifold );

	int yTarget = 1;
	if (!isA) {
		yTarget = -1;
	}

  std::cout << "BeginContact\n";
	if (worldManifold.normal.x == 0 && worldManifold.normal.y == yTarget)
	{
		std::cout << "Grounded\n";
		auto &moveComp = m_Scene->GetRegistry().get<MoveComponent>(m_Entity);
		moveComp.m_NumGrounds++;
		moveComp.m_GroundFixtures.emplace_back(otherFixtureData);

	}
}

void PlayerFixtureData::EndContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA)
{
	auto &moveComp = m_Scene->GetRegistry().get<MoveComponent>(m_Entity);
	auto iter = std::find(moveComp.m_GroundFixtures.begin(), moveComp.m_GroundFixtures.end(), otherFixtureData);
	bool success = false;
	if (iter != moveComp.m_GroundFixtures.end())
	{
		moveComp.m_GroundFixtures.erase(iter);
		success = true;
	}
	if (success)
	{
		moveComp.m_NumGrounds--;
	}
}
