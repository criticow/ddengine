#pragma once

#include <ddenginepch.hpp>

class Transform;

struct TransformCreateInfo
{
  Transform *parentTransform = nullptr;
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 size = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
};

class Transform
{
  public:
  Transform *parentTransform = nullptr;
  glm::vec3 position;
  glm::vec3 size;
  glm::vec3 rotation;

  Transform(): Transform(TransformCreateInfo{}) {};
  Transform(TransformCreateInfo transformCreateInfo);

  glm::mat4 getModel();
};