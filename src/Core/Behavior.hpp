#pragma once

#include <iostream>
#include "Heap.hpp"

enum Status
{
  BH_INVALID,
  BH_SUCCESS,
  BH_FAILURE,
  BH_RUNNING
};

class Behavior : public Heap
{
public:
  Behavior(class Scene* scene): Heap(scene), m_Status(BH_INVALID) {}
  virtual ~Behavior() {}

  Status Tick()
  {
    if (m_Status != BH_RUNNING) OnIntialize();
    m_Status = Update();
    if (m_Status != BH_RUNNING) OnTerminate(m_Status);
    return m_Status;
  }

  virtual void OnIntialize() {}
  virtual Status Update() {}
  virtual void OnTerminate(Status status) {}

protected:
  class Scene* m_Scene;
  Status m_Status;
};
