#pragma once

#include <ddenginepch.hpp>

class Transform;

struct TransformCreateInfo
{
  Transform *parentTransform = nullptr;
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 size = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
  int layer = 0;
};

class Transform
{
  public:
  Transform *parentTransform = nullptr;
  glm::vec3 position;
  glm::vec3 size;
  glm::vec3 rotation;
  int layer;

  Transform(): Transform(TransformCreateInfo{}) {};
  Transform(TransformCreateInfo transformCreateInfo);
  Transform(const Transform &other);

  glm::mat4 getModel();
};