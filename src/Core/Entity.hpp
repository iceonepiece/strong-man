#pragma once

#include "../External/entt/entt.hpp"
#include "Scene.hpp"

class Entity
{
public:
	Entity(entt::entity id, Scene* scene): m_Id(id), m_Scene(scene) {}

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		T& component = m_Scene->m_Registry.emplace<T>(m_Id, std::forward<Args>(args)...);
		return component;
	}

	Scene* GetScene() { return m_Scene; }

private:
	entt::entity m_Id;
	Scene* m_Scene;
};
