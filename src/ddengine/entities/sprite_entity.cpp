#include "sprite_entity.hpp"

#include <ddengine/core/engine.hpp>

SpriteEntity::SpriteEntity(const Transform &transform, const Sprite &sprite)
{
  this->transform = transform;
  this->sprite = sprite;

  this->instanceIndex = Engine::quadRenderer.addInstance(this->sprite.getInstanceData(this->transform));
}

void SpriteEntity::update()
{
  auto &quadInstance = Engine::quadRenderer.instancesData[this->instanceIndex];
  quadInstance = this->sprite.getInstanceData(this->transform);
}