#pragma once

#include <ddenginepch.hpp>

#include <ddengine/renderers/renderer.hpp>

// QID - QuadInstanceData
#define QID_DISPLAY_ENABLED 0
#define QID_DISPLAY_DISABLED 1
#define QID_DISPLAY_DELETED 2

struct QuadInstanceData
{
  // C++ and shader usage
  glm::mat4 model;        // 64 bytes
  glm::vec4 color;        // 16 bytes
  glm::vec4 strokeColor;  // 16 bytes
  glm::vec4 texCoords1;   // 16 bytes
  glm::vec4 texCoords2;   // 16 bytes
  int textureID;          // 4 bytes
  int isText;             // 4 bytes
  int layer;              // 4 bytes
  int display;            // 4 bytes
};

class QuadRenderer : public Renderer<QuadInstanceData>
{
  public:
  QuadRenderer();
  void onSetup() override;
  void onRender(glm::mat4 projection) override;
};