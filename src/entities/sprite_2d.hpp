#pragma once

#include "../ddenginepch.hpp"
#include "../components/transform.hpp"
#include "../components/quad.hpp"
#include "../util/color.hpp"
#include "../renderers/quad_renderer.hpp"

struct Sprite2DCreateInfo
{
  Transform *parentTransform = nullptr;
  Texture *texture = nullptr;
  glm::vec2 position = glm::vec2(0.0f);
  glm::vec2 size = glm::vec2(0.0f);
  glm::vec4 dimensions = glm::vec4(0.0f);
  float rotation = 0.0f;
  int layer = 0;
  Color color = Color(255);
  bool flipX = false;
  bool flipY = false;
  InstanceState state = InstanceState::DISABLED;
};

class Sprite2D
{
  public:
  Sprite2D(void) = default;
  Sprite2D(Sprite2DCreateInfo createInfo);

  void move(const glm::vec2 &velocity);
  void flip(bool flipX, bool flipY);

  void hide();
  void show();
  void setPosition(const glm::vec2 &position);
  void setRotation(float rotation);
  virtual void update();

  protected:
  bool changed;
  unsigned int instanceIndex;
  Transform transform;
  Quad quad;
};