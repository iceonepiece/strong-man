#pragma once

#include "Behavior.hpp"

class Composite : public Behavior
{
public:
  Composite(class Scene* scene) : Behavior(scene) {}
  void AddChild(Behavior* child) { m_Children.push_back(child); }

protected:
  std::vector<Behavior*> m_Children;
};

class Selector : public Composite
{
public:
  Selector(class Scene* scene) : Composite(scene) {}

  void OnIntialize()
  {
    m_CurrentChild = m_Children.begin();
  }

  Status Update()
  {
    while (m_CurrentChild != m_Children.end())
    {
      Status status = (*m_CurrentChild)->Tick();

      if (status != BH_FAILURE)
      {
        return status;
      }

      m_CurrentChild++;
    }

    return BH_FAILURE;
  }

private:
  std::vector<Behavior*>::iterator m_CurrentChild;
};

class Sequence : public Composite
{
public:
  Sequence(class Scene* scene) : Composite(scene) {}

  void OnIntialize()
  {
    m_CurrentChild = m_Children.begin();
  }

  Status Update()
  {
    while (m_CurrentChild != m_Children.end())
    {
      Status status = (*m_CurrentChild)->Tick();

      if (status != BH_SUCCESS)
      {
        return status;
      }

      m_CurrentChild++;
    }

    return BH_SUCCESS;
  }

private:
  std::vector<Behavior*>::iterator m_CurrentChild;
};

class ShoutAction : public Behavior
{
public:
  ShoutAction(class Scene* scene, std::string text): Behavior(scene) , m_Text(text) {}

  Status Update()
  {
    std::cout << "Shout: " << m_Text << std::endl;
    return BH_SUCCESS;
  }

private:
  std::string m_Text;
};
