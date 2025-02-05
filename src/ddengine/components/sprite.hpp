#pragma once

#include <ddenginepch.hpp>
#include <ddengine/resources/texture.hpp>
#include <ddengine/renderers/quad_renderer.hpp>

struct SpriteCreateInfo
{
  Texture *texture = nullptr;
  glm::vec4 dimensions = glm::vec4(0.0f);
  glm::vec4 color = glm::vec4(0.0f);
  bool flipX = false;
  bool flipY = false;
  bool isText = false;
  int layer = 0;
  int display = QID_DISPLAY_DISABLED;
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
  int layer;
  int display;

  Sprite();
  Sprite(SpriteCreateInfo spriteCreateInfo);

  std::pair<glm::vec4, glm::vec4> getTexCoords();
};