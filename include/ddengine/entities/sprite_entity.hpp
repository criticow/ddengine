#pragma once

#include <ddenginepch.hpp>
#include <ddengine/components/transform.hpp>
#include <ddengine/components/sprite.hpp>

class SpriteEntity
{
  public:
  unsigned int instanceIndex;
  Transform transform;
  Sprite sprite;

  SpriteEntity(const Transform &transform, const Sprite &sprite);

  void update();
};