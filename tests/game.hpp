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
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
    auto font = resourceManager.addResource<Font>("dogica_font", Font(FontCreateInfo{
      .name = "dogica",
      .path = "c:/dev/ddengine/examples/data/fonts/comic.ttf",
      .size = 48,
      .pixelated = true
    }));

    LOGGER_DEBUG(font);

    auto font2 = resourceManager.addResource<Font>("dogica_font_16", Font(FontCreateInfo{
      .name = "dogica_16",
      .path = "c:/dev/ddengine/examples/data/fonts/dogica.ttf",
      .size = 160,
      .pixelated = true
    }));

    LOGGER_DEBUG(font2);

    auto font3 = resourceManager.addResource<Font>("dogica_font_64", Font(FontCreateInfo{
      .name = "dogica_64",
      .path = "c:/dev/ddengine/examples/data/fonts/arial.ttf",
      .size = 64,
      .pixelated = true
    }));

    LOGGER_DEBUG(font3);

    Text t1 = Text(TextCreateInfo{
      .font = font,
      .value = "Test",
      .position = glm::vec2(0.0f),
      .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
    });

    Text t2 = Text(TextCreateInfo{
      .font = font2,
      .value = "Test 2",
      .position = glm::vec2(100.0f),
      .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
    });

    Text t3 = Text(TextCreateInfo{
      .font = font3,
      .value = "Test 3",
      .position = glm::vec2(200.0f),
      .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
    });
  };

  void onRender() override
  {
  };
};