#pragma once

#include <ddenginepch.hpp>
#include <ddengine/util/random.hpp>
#include <ddengine/entities/sprite_2d.hpp>

struct Animation
{
  std::string name = "";
  float duration = 0;
  std::vector<glm::vec4> frames;
};

class AnimatedSprite2D : public Sprite2D
{
  public:
  AnimatedSprite2D(void) = default;
  AnimatedSprite2D(Sprite2DCreateInfo createInfo): Sprite2D(createInfo)
  {
    this->uuid = Random::UUID();
    this->isPlaying = false;
  };

  void addAnimation(const std::string &name, float duration, const std::vector<glm::vec4> &frames);
  void play(const std::string &name);
  void stop();
  void pause();
  void update() override;

  private:
  bool isPlaying;
  std::string uuid;
  unsigned int animationIndex;
  std::string currentAnimation;
  std::unordered_map<std::string, Animation> animations;

  bool hasAnimation(const std::string &name);
  void animate();
  void reset();
};