#pragma once

#include <ddengine/ddengine.hpp>

std::vector<Text> texts;
Transform transform;
QuadInstanceData qid;
int index;

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
      window.setTitle(std::format("{:.2f} ms, {:.2f} fps", tempo.ms, tempo.fps));
    }

    transform.rotation.z += 10.0f * tempo.deltaTime;
    quadRenderer.instancesData[index].model = transform.getModel();

    for(auto &text : texts)
    {
      text.setValue(std::format("{}, {}", window.mouse.x, window.mouse.y));
    }
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
    window.setColor(0.1f, 0.2f, 0.3f, 1.0f);

    auto font = resourceManager.setFont("dogica", "data/fonts/dogica.ttf", 16, true);
    auto font2 = resourceManager.setFont("arial", "data/fonts/arial.ttf", 16, true);
    auto font3 = resourceManager.setFont("comic", "data/fonts/comic.ttf", 16, true);

    transform.size = glm::vec3(200.0f, 64.0f, 0.0f);
    transform.position = glm::vec3(
      window.resolutionWidth * 0.5f - transform.size.x * 0.5f,
      window.resolutionHeight * 0.5f - transform.size.y * 0.5f,
      0.0f
    );
    transform.rotation = glm::vec3(0.0f, 0.0f, 45.0f);

    texts.push_back(Text(TextCreateInfo{
      .font = font,
      .parentTransform = &transform,
      .value = "12345",
      .position = glm::vec2(0.0f, 0.0),
      .color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
      .layer = 1
    }));

    texts.push_back(Text(TextCreateInfo{
      .font = font2,
      .parentTransform = &transform,
      .value = "12345",
      .position = glm::vec2(0.0f, font->maxHeight),
      .color = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
      .layer = 1
    }));

    texts.push_back(Text(TextCreateInfo{
      .font = font3,
      .parentTransform = &transform,
      .value = "12345",
      .position = glm::vec2(0.0f, font2->maxHeight * 2.0f),
      .color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
      .layer = 1
    }));

    qid.color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    qid.model = transform.getModel();
    qid.textureID = -1;

    index = quadRenderer.addInstance(qid);

    lineRenderer.instancesData.emplace_back(glm::vec2(window.resolutionWidth * 0.5f, 0.0f), glm::vec2(window.resolutionWidth * 0.5f, window.resolutionHeight), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
    lineRenderer.instancesData.emplace_back(glm::vec2(0.0f, window.resolutionHeight * 0.5f), glm::vec2(window.resolutionWidth, window.resolutionHeight * 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
  };

  void onRender() override
  {
  };
};

int main()
{
  Game game(1280, 720, 1280, 720, "Game");
  game.run();
}