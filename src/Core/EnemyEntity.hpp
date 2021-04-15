#pragma once

#include "Behaviors.hpp"

class EnemyEntity : public Entity
{
public:
	EnemyEntity(Scene* scene)
		:Entity(scene)
		,m_BehaviorRoot(nullptr)
	{
		//m_BehaviorRoot = new Selector();
		m_BehaviorRoot = new Sequence();
		m_BehaviorRoot->AddChild(new ShoutAction("GOLD"));
		m_BehaviorRoot->AddChild(new ShoutAction("SILVER"));
		m_BehaviorRoot->AddChild(new ShoutAction("BRONZE"));

		AddComponent<AIComponent>(m_BehaviorRoot);
  }

	~EnemyEntity()
	{
		if (m_BehaviorRoot)
		{
			delete m_BehaviorRoot;
		}
	}

private:
	Composite* m_BehaviorRoot;
};
