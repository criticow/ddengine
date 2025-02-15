#pragma once

#include <ddenginepch.hpp>
#include <ddengine/resources/texture.hpp>
#include <ddengine/renderers/quad_renderer.hpp>
#include <ddengine/components/transform.hpp>

struct QuadCreateInfo
{
  Texture *texture = nullptr;
  glm::vec4 dimensions = glm::vec4(0.0f);
  glm::vec4 color = glm::vec4(0.0f);
  bool flipX = false;
  bool flipY = false;
  bool isText = false;
  InstanceState state;
};

class Quad
{
  public:
  Texture *texture = nullptr;
  glm::vec4 dimensions;
  glm::vec4 color;
  bool flipX;
  bool flipY;
  bool isText;
  InstanceState state;

  Quad();
  Quad(QuadCreateInfo createInfo);
  Quad(const Quad &other);

  std::pair<glm::vec4, glm::vec4> getTexCoords();
  QuadInstanceData getData(Transform &transform);
};