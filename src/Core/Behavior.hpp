#pragma once

#include <iostream>

enum Status
{
  BH_INVALID,
  BH_SUCCESS,
  BH_FAILURE,
  BH_RUNNING
};

class Behavior
{
public:
  Behavior(): m_Status(BH_INVALID) {}
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

private:
  Status m_Status;
};
