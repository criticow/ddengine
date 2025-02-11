#pragma once

#include <ddenginepch.hpp>
#include <ddengine/renderers/renderer.hpp>

struct LineCreateInfo
{
  glm::vec2 start = glm::vec2(0.0f);
  glm::vec2 end = glm::vec2(0.0f);
  glm::vec4 color = glm::vec4(0.0f);
  int layer = 0;
  InstanceState state = InstanceState::ENABLED;
};

class Line
{
  public:
  Line(void) = default;
  Line(LineCreateInfo createInfo);

  private:
  glm::vec2 start;
  glm::vec2 end;
  glm::vec4 color;
  int layer;
  InstanceState state;
  int instanceIndex;
  bool changed;
};