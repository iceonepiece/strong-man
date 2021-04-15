#pragma once

#include "Behavior.hpp"

class MockBehavior : public Behavior
{
public:
  Status Update()
  {
    std::cout << "MockBehavior Update()" << std::endl;
    return BH_RUNNING;
  }
};


class Composite : public Behavior
{
public:
  virtual ~Composite()
  {
    std::cout << "Composite destructor()" << std::endl;
    for (auto child : m_Children)
  	{
  		delete child;
  	}
  	m_Children.clear();
  }

  void AddChild(Behavior* child) { m_Children.push_back(child); }
  //void removeChild(Behavior*);

protected:
  std::vector<Behavior*> m_Children;
};

class Selector : public Composite
{
public:
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
  ShoutAction(std::string text): m_Text(text) {}

  Status Update()
  {
    std::cout << "Shout: " << m_Text << std::endl;
    return BH_SUCCESS;
  }

private:
  std::string m_Text;
};
