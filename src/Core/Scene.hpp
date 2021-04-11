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
	void Render(SDL_Renderer* renderer);

	class Entity CreateEntity();

protected:
	class Game* m_Game;
	entt::registry m_Registry;

	Physics m_Physics;

	friend class Entity;
};
