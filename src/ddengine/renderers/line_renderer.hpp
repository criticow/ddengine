#pragma once

#include <ddenginepch.hpp>

#include <ddengine/renderers/renderer.hpp>

struct LineInstanceData
{
  glm::vec2 start;   // 8 bytes
  glm::vec2 end;     // 8 bytes
  glm::vec4 color;   // 16 bytes
  int layer;
  InstanceState state;
  int padding[2];
};

class LineRenderer : public Renderer<LineInstanceData>
{
  public:
  LineRenderer();
  void onSetup() override;
  void onRender(glm::mat4 projection) override;
};