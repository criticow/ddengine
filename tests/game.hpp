#pragma once

#include <ddengine/ddengine.hpp>

AnimatedSprite2D *s = nullptr;
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
      flipX = true;
      s->play("walk");
    }

    if(input.held(ACTION_RIGHT))
    {
      velocity.x += speed * tempo.deltaTime;
      flipX = false;
      s->play("walk");
    }

    if(input.held(ACTION_ACCEPT))
    {
      rotation += 5.0f;
    }

    if(input.held(ACTION_JUMP))
    {
      s->play("fire");
      velocity = glm::vec2(0.0f);
    }
    else
    {
      if(velocity == glm::vec2(0.0f))
      {
        s->play("idle");
      }
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
    s = new AnimatedSprite2D(Sprite2DCreateInfo{
      .texture = texture,
      .size = glm::vec2(128.0f),
      .dimensions = glm::vec4(0.0f, 0.0f, 32.0f, 32.0f),
      .state = InstanceState::ENABLED,
    });

    s->addAnimation("idle", 500.0f, {
      glm::vec4(0.0f,   0.0f, 32.0f, 32.0f),
      glm::vec4(32.0f,  0.0f, 32.0f, 32.0f),
      glm::vec4(64.0f,  0.0f, 32.0f, 32.0f),
      glm::vec4(96.0f,  0.0f, 32.0f, 32.0f),
    });

    s->addAnimation("walk", 500.0f, {
      glm::vec4(0.0f,   32.0f, 32.0f, 32.0f),
      glm::vec4(32.0f,  32.0f, 32.0f, 32.0f),
      glm::vec4(64.0f,  32.0f, 32.0f, 32.0f),
      glm::vec4(96.0f,  32.0f, 32.0f, 32.0f),
      glm::vec4(128.0f, 32.0f, 32.0f, 32.0f),
      glm::vec4(160.0f, 32.0f, 32.0f, 32.0f),
      glm::vec4(192.0f, 32.0f, 32.0f, 32.0f),
      glm::vec4(224.0f, 32.0f, 32.0f, 32.0f),
    });

    s->addAnimation("fire", 500.0f, {
      glm::vec4(0.0f,   64.0f, 32.0f, 32.0f),
      glm::vec4(32.0f,  64.0f, 32.0f, 32.0f),
      glm::vec4(64.0f,  64.0f, 32.0f, 32.0f),
      glm::vec4(96.0f,  64.0f, 32.0f, 32.0f),
      glm::vec4(128.0f, 64.0f, 32.0f, 32.0f),
    });
  };

  void onRender() override
  {
  };
};