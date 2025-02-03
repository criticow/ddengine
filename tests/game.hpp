#pragma once

#include <ddengine/ddengine.hpp>

class Game : public Engine
{
  public:
  Game(int width, int height, int resWidth, int resHeight, const char *title) : 
    Engine(width, height, resWidth, resHeight, title){};
  // This method is called in the end of the main update
  void onUpdate() override
  {
    if(tempo.justUpdated)
    {
      float mouseX = window.mouse.clientX;
      float mouseY = window.mouse.clientY;

      const float scaleX = static_cast<float>(window.resolutionWidth) / window.width;
      const float scaleY = static_cast<float>(window.resolutionHeight) / window.height;

      auto worldX = window.mouse.x;
      auto worldY = window.mouse.y;


      window.setTitle(std::format(
        "Mouse Position - Window Pos: {}, {} | World Pos: {}, {}",
        mouseX, mouseY,
        worldX, worldY
      ));
    }
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
    Font *font = resourceManager.setFont("arial", "c:/dev/ddengine/examples/data/fonts/arial.ttf", 16);

    glm::vec2 size(64.0f);

    std::vector<glm::vec2> positions = {
      glm::vec2(0.0f, 0.0f),
      glm::vec2(window.resolutionWidth * 0.5f - size.x * 0.5f, 0.0f),
      glm::vec2(window.resolutionWidth - size.x, 0.0f),

      glm::vec2(0.0f, window.resolutionHeight * 0.5f - size.y * 0.5f),
      glm::vec2(window.resolutionWidth * 0.5f - size.x * 0.5f, window.resolutionHeight * 0.5f - size.y * 0.5f),
      glm::vec2(window.resolutionWidth - size.x, window.resolutionHeight * 0.5f - size.y * 0.5f),

      glm::vec2(0.0f, window.resolutionHeight - size.y),
      glm::vec2(window.resolutionWidth * 0.5f - size.x * 0.5f, window.resolutionHeight - size.y),
      glm::vec2(window.resolutionWidth - size.x, window.resolutionHeight - size.y)
    };

    for(auto position : positions)
    {
      glm::mat4 model(1.0f);

      model = glm::translate(model, glm::vec3(position, 0.0f));
      model = glm::scale(model, glm::vec3(size, 0.0f));

      QuadInstanceData data;
      data.model = model;
      data.layer = 0;
      data.isText = false;
      data.textureID = -1;
      data.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
      data.strokeColor = glm::vec4(0.0f);
      data.isDeleted = false;
      quadRenderer.instancesData.push_back(data);
    }

    lineRenderer.instancesData.emplace_back(glm::vec2(window.resolutionWidth * 0.5f, 0.0f), glm::vec2(window.resolutionWidth * 0.5f, window.resolutionHeight), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
    lineRenderer.instancesData.emplace_back(glm::vec2(0.0f, window.resolutionHeight * 0.5f), glm::vec2(window.resolutionWidth, window.resolutionHeight * 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
  };

  void onRender() override {};
};