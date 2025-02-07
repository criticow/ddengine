#pragma once

#include <ddengine/ddengine.hpp>

EntityManager entityManager;

class Game : public Engine
{
  public:
  Game(int width, int height, int resWidth, int resHeight, const char *title) : 
    Engine(width, height, resWidth, resHeight, title){};

  // This method is called in the end of the main update
  void onUpdate() override
  {
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
    auto entity = entityManager.create();

    auto c1 = entityManager.addComponent<Transform>(entity, Transform({
      nullptr,
      glm::vec3(1.0f),
      glm::vec3(2.0f),
      glm::vec3(3.0f)
    }));

    auto c2 = entityManager.addComponent<Text>(entity, Text{});

    auto font = resourceManager.addResource<Font>("dogica", Font{
      {
        .name = "dogica",
        .path = "c:/dev/ddengine/examples/data/fonts/dogica.ttf",
        .size = 16,
        .pixelated = true
      }
    });

    Text text(TextCreateInfo{
      .font = font,
      .value = "Teste",
      .position = glm::vec3(64.0f),
      .color = glm::vec4(1.0f)
    });
  };

  void onRender() override
  {
  };
};