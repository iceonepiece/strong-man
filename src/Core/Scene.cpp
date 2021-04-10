#include "Scene.hpp"

Scene::Scene(class Game* game)
  :m_Game(game)
{}

Scene::~Scene()
{
  for (auto entity : m_Entities)
  {
    delete entity;
  }
  m_Entities.clear();
}
