#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../External/entt/entt.hpp"
#include "Input.hpp"
#include "Physics.hpp"

class Scene
{
public:
	Scene(class Game* game);
	virtual ~Scene();

	void ProcessInput(Input& input);
	void Update(float deltaTime);
	void Render(class Renderer* renderer);

	Physics& GetPhysics() { return m_Physics; }

	class Entity CreateEntity();

protected:
	class Game* m_Game;
	entt::registry m_Registry;

	Physics m_Physics;

	friend class Entity;
};
