#pragma once

#include <ddenginepch.hpp>

#include <ddengine/resources/font.hpp>
#include <ddengine/renderers/quad_renderer.hpp>
#include <ddengine/components/sprite.hpp>
#include <ddengine/components/transform.hpp>

struct TextCreateInfo
{
  Font *font = nullptr;
  Transform *parentTransform = nullptr;
  std::string value;
  glm::vec2 position = glm::vec2(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
  glm::vec4 color = glm::vec4(0.0f);
  int layer = 0;
};

class Text
{
  public:
  Font *font;
  Transform *parentTransform;
  std::string value;
  glm::vec2 position;
  glm::vec3 rotation;
  glm::vec4 color;
  int layer;

  Text(){};
  Text(TextCreateInfo textCreateInfo);

  void setValue(const std::string &value);
  void setPosition(const glm::vec2 &position);

  private:
  std::vector<int> instances;

  void setup();
};