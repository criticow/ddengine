#pragma once

#include "../ddenginepch.hpp"
#include "../resources/texture.hpp"
#include "../renderers/quad_renderer.hpp"
#include "transform.hpp"

struct SpriteCreateInfo
{
  Texture *texture = nullptr;
  glm::vec4 dimensions = glm::vec4(0.0f);
  glm::vec4 color = glm::vec4(0.0f);
  bool flipX = false;
  bool flipY = false;
  bool isText = false;
  InstanceState state;
};

class Sprite
{
  public:
  Texture *texture = nullptr;
  glm::vec4 dimensions;
  glm::vec4 color;
  bool flipX;
  bool flipY;
  bool isText;
  InstanceState state;

  Sprite();
  Sprite(SpriteCreateInfo spriteCreateInfo);
  Sprite(const Sprite &other);

  std::pair<glm::vec4, glm::vec4> getTexCoords();
  QuadInstanceData getInstanceData(Transform &transform);
};