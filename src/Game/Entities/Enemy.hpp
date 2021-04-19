#pragma once

#include "../../Core/Behavior.hpp"
#include "../../Core/Behaviors.hpp"
#include "../Components/Components.hpp"

class Enemy
{
public:
  static entt::entity Create(EntityFactory* factory)
  {
    auto entity = factory->Entity();

    Fixture bodyFixture(b2Vec2(2.0f, 3.0f), b2Vec2(0.0f, 0.0f));
		FixtureData* m_FixtureData = new FixtureData(factory->GetScene(), entity, "PLAYER");
		bodyFixture.SetFixtureData(m_FixtureData);
		std::vector<Fixture> fixtures { bodyFixture };
		factory->AddComponent<BoxComponent>(entity, factory->GetScene()->GetPhysics().CreateDynamicBody(4.0f, 10.0f, fixtures));

		Sequence* m_BehaviorRoot = new Sequence(factory->GetScene());
		m_BehaviorRoot->AddChild(new ShoutAction(factory->GetScene(), "GOLD"));
		m_BehaviorRoot->AddChild(new ShoutAction(factory->GetScene(), "SILVER"));

		factory->AddComponent<AIComponent>(entity, m_BehaviorRoot);

    return entity;
  }
};
