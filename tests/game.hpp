#pragma once

#include <ddengine/ddengine.hpp>

Sprite2D *s = nullptr;
float rotation = 0.0f;
float flipX = false;
float flipY = false;

class Game : public Engine
{
  public:
  Game(int width, int height, int resWidth, int resHeight, const char *title) : 
    Engine(width, height, resWidth, resHeight, title){};

  // This method is called in the end of the main update
  void onUpdate() override
  {
    float speed = 400.0f;
    glm::vec2 velocity(0.0f);

    if(input.held(ACTION_LEFT))
    {
      velocity.x -= speed * tempo.deltaTime;
    }

    if(input.held(ACTION_RIGHT))
    {
      velocity.x += speed * tempo.deltaTime;
    }

    if(input.held(ACTION_ACCEPT))
    {
      rotation += 5.0f;
    }

    if(input.pressed(KEY_1))
    {
      flipX = !flipX;
    }

    if(input.pressed(KEY_2))
    {
      flipY = !flipY;
    }

    s->flip(flipX, flipY);
    s->setRotation(rotation);
    s->move(velocity);
    s->update();
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
    auto texture = resourceManager.addResource<Texture>("cadet", TextureCreateInfo{.path = "c:/dev/ddengine/data/textures/cadet.png"});
    s = new Sprite2D(Sprite2DCreateInfo{
      .texture = texture,
      .size = glm::vec2(128.0f),
      .dimensions = glm::vec4(0.0f, 0.0f, 32.0f, 32.0f),
      .state = InstanceState::ENABLED,
    });
  };

  void onRender() override
  {
  };
};