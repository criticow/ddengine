#include "sprite_2d.hpp"

#include <ddengine/core/engine.hpp>

Sprite2D::Sprite2D(Sprite2DCreateInfo createInfo)
{
  this->transform = Transform(TransformCreateInfo{
    .parentTransform = createInfo.parentTransform,
    .position = createInfo.position,
    .size = createInfo.size,
    .rotation = createInfo.rotation,
    .layer = createInfo.layer
  });

  this->quad = Quad(QuadCreateInfo{
    .texture = createInfo.texture,
    .dimensions = createInfo.dimensions,
    .color = createInfo.color,
    .flipX = createInfo.flipX,
    .flipY = createInfo.flipY,
    .isText = false,
    .state = createInfo.state
  });

  this->instanceIndex = Engine::quadRenderer.addInstance(this->quad.getData(this->transform));
  this->changed = false;
}

void Sprite2D::update()
{
  if(!this->changed)
  {
    return;
  }

  this->changed = false;
  auto &quadInstance = Engine::quadRenderer.instancesData[this->instanceIndex];
  quadInstance = this->quad.getData(this->transform);
}

void Sprite2D::move(const glm::vec2 &velocity)
{
  if(velocity == glm::vec2(0.0f))
  {
    return;
  }

  this->transform.position += velocity;
  this->changed = true;
}

void Sprite2D::setPosition(const glm::vec2 &position)
{
  if(this->transform.position == position)
  {
    return;
  }

  this->transform.position = position;
  this->changed = true;
}

void Sprite2D::setRotation(float rotation)
{
  if(this->transform.rotation == rotation)
  {
    return;
  }

  this->transform.rotation = rotation;
  this->changed = true;
}

void Sprite2D::flip(bool flipX, bool flipY)
{
  if(this->quad.flipX == flipX && this->quad.flipY == flipY)
  {
    return;
  }

  this->quad.flipX = flipX;
  this->quad.flipY = flipY;
  this->changed = true;
}