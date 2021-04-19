#include "Heap.hpp"
#include "Scene.hpp"

#pragma once

Heap::Heap(Scene* scene)
  :m_Scene(scene)
{
  m_Scene->AddHeap(this);
}

Heap::~Heap()
{

}
