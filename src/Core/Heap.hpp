#pragma once

class Heap
{
public:
  Heap(class Scene* scene);
  virtual ~Heap();

protected:
  class Scene* m_Scene;
};
