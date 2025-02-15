#pragma once

#include "../ddenginepch.hpp"

class Camera
{
  public:
  glm::vec2 position;
  float rotation;
  glm::mat4 projection;
  glm::mat4 view;

  Camera(void) = default;
  Camera(glm::vec2 position, float rotation);

  void update(int resolutionWidth, int resolutionHeight);
};