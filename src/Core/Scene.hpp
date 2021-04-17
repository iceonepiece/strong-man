#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../External/entt/entt.hpp"
#include "Math.hpp"
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

	class Font* GetFont(const std::string& fileName);

protected:
	class Game* m_Game;

	std::vector<class UI*> m_UIs;
	std::unordered_map<std::string, class Font*> m_Fonts;

	entt::registry m_Registry;

	Physics m_Physics;
	Camera m_Camera;

	friend class Entity;
};
