#pragma once

#include "../External/entt/entt.hpp"
#include "Scene.hpp"

class Entity
{
public:
	Entity(Scene* scene)
		:m_Scene(scene)
		,m_Id(scene->m_Registry.create())
	{

	}

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		T& component = m_Scene->m_Registry.emplace<T>(m_Id, std::forward<Args>(args)...);
		return component;
	}

	Scene* GetScene() { return m_Scene; }
	entt::entity GetId() { return m_Id; }

protected:
	entt::entity m_Id;
	Scene* m_Scene;
};
