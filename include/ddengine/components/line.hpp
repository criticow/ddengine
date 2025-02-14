#pragma once

#include <ddenginepch.hpp>
#include <ddengine/renderers/line_renderer.hpp>

struct LineCreateInfo
{
  glm::vec2 position = glm::vec2(0.0f);
  glm::vec2 length = glm::vec2(0.0f);
  glm::vec4 color = glm::vec4(0.0f);
  int layer = 0;
  InstanceState state = InstanceState::ENABLED;
};


/*
  The orientation of the line is based on the length, length.x > 0 the line will 
  go into the length.x direction, the same with length.y
*/
class Line
{
  public:
  Line(void) = default;
  Line(LineCreateInfo createInfo);

  void setPosition(const glm::vec2 &position);
  void setLength(const glm::vec2 &length);
  void setColor(const glm::vec4 &color);
  void setState(InstanceState state);
  void setLayer(int layer);
  void update();

  private:
  glm::vec2 position;
  glm::vec2 length;
  glm::vec4 color;
  int layer;
  InstanceState state;
  int instanceIndex;
  bool changed;

  LineInstanceData generateData();
};