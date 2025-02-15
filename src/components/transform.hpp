#pragma once

#include "../ddenginepch.hpp"

class Transform;

struct TransformCreateInfo
{
  Transform *parentTransform = nullptr;
  glm::vec2 position = glm::vec2(0.0f);
  glm::vec2 size = glm::vec2(0.0f);
  float rotation = 0.0f;
  int layer = 0;
};

class Transform
{
  public:
  Transform *parentTransform = nullptr;
  glm::vec2 position;
  glm::vec2 size;
  float rotation;
  int layer;

  Transform(): Transform(TransformCreateInfo{}) {};
  Transform(TransformCreateInfo transformCreateInfo);
  Transform(const Transform &other);

  glm::mat4 getModel();
};