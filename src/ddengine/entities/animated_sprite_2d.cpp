#include "aminated_sprite_2d.hpp"

#include <ddengine/core/engine.hpp>

void AnimatedSprite2D::update()
{
  if(this->isPlaying && !this->animations.empty())
  {
    this->animate();
  }

  Sprite2D::update();
}

void AnimatedSprite2D::animate()
{
  auto animation = this->animations[currentAnimation];

  if(Engine::tempo.hasPassed(this->uuid, animation.duration / animation.frames.size()))
  {
    this->animationIndex++;

    if(this->animationIndex > animation.frames.size() -1)
    {
      this->animationIndex = 0;
    }

    this->quad.dimensions = animation.frames[this->animationIndex];
    this->changed = true;
  }
}

bool AnimatedSprite2D::hasAnimation(const std::string &name)
{
  return this->animations.find(name) != this->animations.end();
}

void AnimatedSprite2D::play(const std::string &name)
{
  ASSERT(this->hasAnimation(name), "Animation with name {} was not found", name);

  if(this->currentAnimation == name)
  {
    this->isPlaying = true;
    return;
  }


  this->currentAnimation = name;
  this->isPlaying = true;
  this->reset();
}

void AnimatedSprite2D::reset()
{
  this->animationIndex = 0;
  Engine::tempo.clearTimepoint(this->uuid);

  auto animation = this->animations[currentAnimation];
  this->quad.dimensions = animation.frames[this->animationIndex];
}

void AnimatedSprite2D::stop()
{
  if(this->currentAnimation.empty() || this->animations.empty())
  {
    return;
  }

  this->isPlaying = false;
  this->changed = true;
  this->reset();
}

void AnimatedSprite2D::pause()
{
  this->isPlaying = false;
}

void AnimatedSprite2D::addAnimation(const std::string &name, float duration, const std::vector<glm::vec4> &frames)
{
  this->animations[name] = Animation{
    .name = name,
    .duration = duration,
    .frames = frames
  };
}