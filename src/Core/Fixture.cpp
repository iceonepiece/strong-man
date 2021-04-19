#include "Fixture.hpp"
#include "Scene.hpp"

FixtureData::FixtureData(Scene* scene, entt::entity entity, std::string tag)
  :Heap(scene)
  ,m_Entity(entity)
  ,m_Tag(tag)
{
  std::cout << "FixtureData constructor: " << m_Tag << std::endl;
}

FixtureData::~FixtureData()
{
  std::cout << "FixtureData destructor: " << m_Tag << std::endl;
}

void FixtureData::BeginContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA)
{

}

void FixtureData::EndContact(FixtureData* otherFixtureData, b2Contact* contact, bool isA)
{

}
