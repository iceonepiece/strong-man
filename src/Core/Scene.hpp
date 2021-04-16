#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../External/entt/entt.hpp"
#include "Input.hpp"
#include "Physics.hpp"
#include "Camera.hpp"

class Scene
{
public:
	Scene(class Game* game);
	virtual ~Scene();

	void ProcessInput(Input& input);
	void Update(float deltaTime);
	void Render(class Renderer* renderer);

	Physics& GetPhysics() { return m_Physics; }
	entt::registry& GetRegistry() { return m_Registry; }

protected:
	class Game* m_Game;
	std::vector<class UI*> m_UIs;

	entt::registry m_Registry;

	Physics m_Physics;
	Camera m_Camera;

	friend class Entity;
};
