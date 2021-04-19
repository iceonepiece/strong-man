#pragma once

class Tile
{
public:
  static entt::entity Create(EntityFactory* factory, float x, float y, float width, float height)
  {
    auto entity = factory->Entity();

    Fixture tileFixture(b2Vec2(width, height), b2Vec2(0.0f, 0.0f));
    tileFixture.SetFixtureData(new FixtureData(factory->GetScene(), entity, "TILE"));
    std::vector<Fixture> tileFixtures { tileFixture };
    factory->AddComponent<BoxComponent>(entity, factory->GetScene()->GetPhysics().CreateStaticBody(x, y, tileFixtures));

    return entity;
  }
};
