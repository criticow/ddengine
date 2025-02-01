#pragma once

#include <ddengine/ddengine.hpp>

class Game : public Engine
{
  public:
  Game(int width, int height, int resWidth, int resHeight, const char *title) : 
    Engine(width, height, resWidth, resHeight, title){};
  // This method is called in the end of the main update
  void onUpdate() override {};
  // This method is called in the end of the main setup
  void onSetup() override {

    glm::mat4 model(1.0f);
    glm::vec3 size = glm::vec3(96.0f, 32.0f, 1.0f);
    model = glm::translate(model, glm::vec3(64.0f, 64.0f, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, size);

    QuadInstanceData data;
    data.model = model;
    data.layer = 0;
    data.isText = false;
    data.textureID = -1;
    data.color = glm::vec4(1.0f);
    data.strokeColor = glm::vec4(0.0f);

    quadRenderer.instancesData.push_back(data);

    std::vector<glm::vec2> quads = {
      glm::vec2(0.0f, 0.0f),
      glm::vec2(32.0f, 0.0f),
      glm::vec2(64.0f, 0.0f),
    };

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(64.0f, 64.0f, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    for(auto quad : quads)
    {
      glm::mat4 quadModel = model;

      quadModel = glm::translate(quadModel, glm::vec3(quad, 0.0f));
      glm::vec3 quadSize = glm::vec3(16.0f, 16.0f, 1.0f);
      quadModel = glm::scale(quadModel, quadSize);

      QuadInstanceData quadData;
      quadData.model = quadModel;
      quadData.layer = 0;
      quadData.isText = false;
      quadData.textureID = -1;
      quadData.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
      quadData.strokeColor = glm::vec4(0.0f);
      quadRenderer.instancesData.push_back(quadData);
    }

  };
  void onRender() override {};
};

int main()
{
  Game game(1280, 720, 1280, 720, "ParentChild");
  game.run();
}