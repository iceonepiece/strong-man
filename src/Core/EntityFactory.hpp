#pragma once

#include "../External/entt/entt.hpp"

class EntityFactory
{
public:
  EntityFactory(class Scene* scene): m_Scene(scene) {}

  entt::entity Entity()
  {
    return m_Scene->m_Registry.create();
  }

  class Scene* GetScene() { return m_Scene; }

  template<typename T, typename... Args>
	entt::entity Create(Args&&... args)
	{
		entt::entity entity = T::Create(this, std::forward<Args>(args)...);
		return entity;
	}

  template<typename T, typename... Args>
	T& AddComponent(entt::entity entity, Args&&... args)
	{
		T& component = m_Scene->m_Registry.emplace<T>(entity, std::forward<Args>(args)...);
		return component;
	}

protected:
  class Scene* m_Scene;
};
