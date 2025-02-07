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
    glm::vec3 velocity(0.0f);
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
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
    int amount = 100000;

    glm::vec3 size(8.0f, 8.0f, 0.0f);
    auto transform = Transform({
      nullptr,
      glm::vec3(8.0f, 8.0f, 0.0f),
      size,
      glm::vec3(0.0f)
    });

    auto sprite = Sprite{SpriteCreateInfo{.color = glm::vec4(1.0f)}};

    e = new SpriteEntity(transform, sprite);
  };

  void onRender() override
  {
  };
};