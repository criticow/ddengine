#pragma once

#include <ddengine/ddengine.hpp>

SpriteEntity *e = nullptr;

class Game : public Engine
{
  public:
  Game(int width, int height, int resWidth, int resHeight, const char *title) : 
    Engine(width, height, resWidth, resHeight, title){};

  // This method is called in the end of the main update
  void onUpdate() override
  {
    glm::vec2 velocity(0.0f);
    float speed = 100.0f;

    if(input.held(ACTION_LEFT))
    {
      velocity.x -= speed * tempo.deltaTime;
    }
    else if(input.held(ACTION_RIGHT))
    {
      velocity.x += speed * tempo.deltaTime;
    }

    if(input.held(ACTION_UP))
    {
      velocity.y -= speed * tempo.deltaTime;
    }
    else if(input.held(ACTION_DOWN))
    {
      velocity.y += speed * tempo.deltaTime;
    }

    e->transform.position += velocity;
    e->update();

    camera.position.x = e->transform.position.x - ( window.resolutionWidth * 0.5f ) + (e->transform.size.x * 0.5f);
    camera.position.y = e->transform.position.y - ( window.resolutionHeight * 0.5f ) + (e->transform.size.y * 0.5f);
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
    glm::vec2 size(8.0f, 8.0f);
    float x = window.resolutionWidth * 0.5f - size.x * 0.5f;
    float y = window.resolutionHeight * 0.5f - size.y * 0.5f;

    auto transform = Transform(TransformCreateInfo{
      .parentTransform = nullptr,
      .position = glm::vec2(x, y),
      .size = size,
      .rotation = 0.0f,
      .layer = 2
    });

    auto sprite = Sprite{SpriteCreateInfo{.color = glm::vec4(1.0f)}};

    e = new SpriteEntity(transform, sprite);

    auto e1 = SpriteEntity(
      Transform{TransformCreateInfo{
        .parentTransform = nullptr,
        .position = glm::vec2(0.0f),
        .size = glm::vec2(32.0f),
        .rotation = 0.0f,
        .layer = 1
      }},
      Sprite{SpriteCreateInfo{
        .color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
      }}
    );

    lineRenderer.instancesData.emplace_back(glm::vec2(window.resolutionWidth * 0.5f, 0.0f), glm::vec2(window.resolutionWidth * 0.5f, window.resolutionHeight), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
    lineRenderer.instancesData.emplace_back(glm::vec2(0.0f, window.resolutionHeight * 0.5f), glm::vec2(window.resolutionWidth, window.resolutionHeight * 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
  };

  void onRender() override
  {
  };
};